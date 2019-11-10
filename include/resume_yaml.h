#ifndef RESUME_YAML_H
#define RESUME_YAML_H

typedef struct YamlParser YamlParser;

typedef struct YamlNode {
    char *key, *val;
} YamlNode;

YamlParser* newYamlParser(char* yaml);
void freeYamlParser(YamlParser *parser);

YamlNode nextNode(YamlParser* parser);

<<<<<<< HEAD
void setStrVal(YamlNode* node, char* dat);
char* getStrVal(YamlNode* node);
=======
void setVal(YamlNode* node, char* dat);
char* getVal(YamlNode* node);
>>>>>>> getStrVal-
#endif
