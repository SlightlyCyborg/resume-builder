#include <string.h>
#include <stdio.h>
#include "resume.h"
#include "resume_yaml.h"

void loadFile(char* buf, char* fname) {
    FILE* f;
    f = fopen(fname, "r");
    fgets(buf, sizeof(buf), f);
}

Resume resumeFromYaml(char* yaml) {
    YamlParser *parser = newYamlParser(yaml);
    YamlNode *root = parseAll(parser);

    Resume resume;

    YamlNode *info = searchMapping(root, "basicInfo");
    resume.basicInfo.name = getVal(searchMapping(info, "name"));
    resume.basicInfo.birthday = getVal(searchMapping(info, "birthdate"));
    resume.basicInfo.location = getVal(searchMapping(info, "location"));
    resume.basicInfo.mtbi = getVal(searchMapping(info, "mtbi"));

    return resume;
}
