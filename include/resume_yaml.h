#ifndef RESUME_YAML_H
#define RESUME_YAML_H

typedef struct YamlParser YamlParser;

typedef struct YamlNode {
    char *key, *val;
    struct YamlNode *child;
} YamlNode;

YamlParser* newYamlParser(char* yaml);
void freeYamlParser(YamlParser *parser);

YamlNode nextNode(YamlParser* parser);

void setVal(YamlNode* node, char* dat);
char* getVal(YamlNode* node);

void setChild(YamlNode *parent, YamlNode *child);
YamlNode *getChild(YamlNode *parent);
#endif
