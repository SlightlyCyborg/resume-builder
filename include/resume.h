#ifndef RESUME_H
#define RESUME_H

#include "resume_yaml.h"

typedef struct Job {
    char *company,
        *startDate,
        *endDate,
        *description,
        *boss,
        *contact;
} Job;

typedef struct BasicInfo {
    char* name;
    char* birthday;
    char* location;
    char* mtbi;
} BasicInfo;

typedef struct Resume {
    BasicInfo basicInfo;
    Job* jobHistory;
    int numJobs;
} Resume;

void loadFile(char* buf, char* f);

Resume resumeFromYaml(char* yaml);
#endif
