#ifndef RESUME_H
#define RESUME_H

typedef struct BasicInfo {
    char* name;
    char* birthday;
    char* location;
    char* mtbi;
} BasicInfo;

typedef struct Resume {
    BasicInfo basicInfo;
} Resume;

void loadFile(char* buf, char* f);

Resume resumeFromYaml(char* yaml);
#endif
