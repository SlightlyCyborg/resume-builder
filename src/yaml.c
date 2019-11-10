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

void freeYamlParser(YamlParser* parser){
    yaml_parser_delete(parser->libyaml_parser);
}

