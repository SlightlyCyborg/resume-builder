#ifndef RESUME_YAML_H
#define RESUME_YAML_H

typedef struct YamlParser YamlParser;

typedef struct YamlNode {
    char *key, *val, *strVal;
    int intVal;
} YamlNode;

YamlParser* newYamlParser(char* yaml);
void freeYamlParser(YamlParser *parser);

YamlNode nextNode(YamlParser* parser);

void setStrVal(YamlNode* node, char* dat);
char* getStrVal(YamlNode* node);
#endif
