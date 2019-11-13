#include <stdlib.h>
#include <stdio.h>
#include <yaml.h>
#include "resume_yaml.h"

typedef struct YamlParser {
    yaml_parser_t *libyaml_parser;
} YamlParser;

YamlParser *newYamlParser(char* yaml){
    YamlParser* parser = (YamlParser *) malloc(sizeof(YamlParser));

    parser->libyaml_parser = (yaml_parser_t *) malloc(sizeof(yaml_parser_t));
    yaml_parser_initialize(parser->libyaml_parser);

    size_t length = strlen(yaml);
    yaml_parser_set_input_string(
            parser->libyaml_parser, (unsigned char*) yaml, length);

    return parser;
}

YamlNode nextNode(YamlParser* parser){
    YamlNode node;
    yaml_event_t event;

    int step = 0;

    while(step < 2) {
        if (!yaml_parser_parse(parser->libyaml_parser, &event)) break;

        if (event.type == YAML_SCALAR_EVENT) {
            if(step == 0) {
                node.key = malloc(strlen((char*) event.data.scalar.value));
                strcpy(node.key,  (char*) event.data.scalar.value);
            } else {
                node.val = malloc(strlen((char*) event.data.scalar.value));
                strcpy(node.val, (char*) event.data.scalar.value);
            }
            step++;
        } else {
            step = 2*(event.type == YAML_STREAM_END_EVENT);
        }
        yaml_event_delete(&event);
    }
    return node;
}


YamlNode *nodeFromScalarEvent(yaml_event_t event) {
    YamlNode *node = (YamlNode *) malloc(sizeof(YamlNode));
    setVal(node, event.data.scalar.value);
    return node;
}

YamlNode* getNextNode(YamlParser *parser);

YamlNode* handleMappingEvent(YamlParser *parser) {
    YamlNode *rv = NULL;
    rv = getNextNode(parser);
    setChild(rv, getNextNode(parser));
    return rv;
}

YamlNode *handleSequenceEvent(YamlParser *parser) {
    YamlNode *rv;
    rv = getNextNode(parser);
    if(rv != NULL) {
        setSibling(rv, handleSequenceEvent(parser));
    }
    return rv;
}

YamlNode* getNextNode(YamlParser *parser) {
    yaml_event_t event;
    YamlNode *rv = NULL;

    if (yaml_parser_parse(parser->libyaml_parser, &event)){
        switch(event.type) {
            case YAML_SCALAR_EVENT:
                rv = nodeFromScalarEvent(event);
                break;
            case YAML_SEQUENCE_START_EVENT:
                rv = handleSequenceEvent(parser);
                break;
            case YAML_MAPPING_START_EVENT:
                rv = handleMappingEvent(parser);
                break;
            case YAML_STREAM_START_EVENT:
            case YAML_DOCUMENT_START_EVENT:
            case YAML_ALIAS_EVENT:
                rv = getNextNode(parser);
            default:
                break;
        }
        yaml_event_delete(&event);
    }
    return rv;

}

YamlNode *parseAll(YamlParser *parser) {
    return getNextNode(parser);
}

/*
YamlNode *parseAll(YamlParser* parser) {
    char* val;
    YamlNode *first, *node, *seqRoot;
    YamlNode **ptr_to_node_ptr = &first;
    yaml_event_t event;
    int done = 0;
    int inSeq = 0;

    while(!done) {
        if (!yaml_parser_parse(parser->libyaml_parser, &event)){
            printf("error\n");
            break;
        }

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                handleScalarEvent(event, ptr_to_node_ptr, inSeq);
                ptr_to_node_ptr = getPtrToNextNodePtr(inSeq, ptr_to_node_ptr);
                break;
            case YAML_SEQUENCE_START_EVENT:
                inSeq = 1;
                break;
            case YAML_MAPPING_START_EVENT:
                handleMappingEvent(parser, event);
            case YAML_STREAM_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }
    return first;
}
*/

void setVal(YamlNode* node, char* dat) {
    char* val = (char*) malloc(sizeof(char) * strlen(dat));
    strcpy(val, dat);
    node->val = val;
}

char* getVal(YamlNode* node) {
    return node->val;
}

void setChild(YamlNode *parent, YamlNode *child) {
    parent->child = child;
}

YamlNode *getChild(YamlNode *parent) {
    return parent->child;
}

void setSibling(YamlNode *node, YamlNode *sibling) {
    node->sibling = sibling;
}

YamlNode *getSibling(YamlNode *node) {
    return node->sibling;
}

void freeYamlParser(YamlParser* parser){
    yaml_parser_delete(parser->libyaml_parser);
}

