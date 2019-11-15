#ifndef RESUME_YAML_H
#define RESUME_YAML_H

typedef struct YamlParser YamlParser;

typedef struct YamlNode {
    char *key, *val;
    struct YamlNode *child, *sibling, *nextInMapping;
} YamlNode;

YamlParser* newYamlParser(char* yaml);
void freeYamlParser(YamlParser *parser);

YamlNode nextNode(YamlParser* parser);

void setVal(YamlNode* node, char* dat);
char* getVal(YamlNode* node);

void setChild(YamlNode *parent, YamlNode *child);
YamlNode *getChild(YamlNode *parent);

void setSibling(YamlNode *node, YamlNode *sibling);
YamlNode *getSibling(YamlNode *node);


void setNextInMapping(YamlNode *node, YamlNode *next);
YamlNode *getNextInMapping();

YamlNode *parseAll(YamlParser* parser);

YamlNode *searchMapping(YamlNode *root, char *key);
#endif
