#include <string.h>
#include <stdio.h>
#include "resume.h"
#include "resume_yaml.h"

#define MAX_JOBS 256

void loadFile(char* buf, char* fname) {
    FILE* f;
    f = fopen(fname, "r");
    fgets(buf, sizeof(buf), f);
}

void setBasicInfo(Resume *resume, YamlNode *info) {
    resume->basicInfo.name = getVal(searchMapping(info, "name"));
    resume->basicInfo.birthday = getVal(searchMapping(info, "birthdate"));
    resume->basicInfo.location = getVal(searchMapping(info, "location"));
    resume->basicInfo.mtbi = getVal(searchMapping(info, "mtbi"));
}

Resume resumeFromYaml(char* yaml) {
    YamlParser *parser = newYamlParser(yaml);
    YamlNode *root = parseAll(parser);

    Resume resume;

    YamlNode *info = searchMapping(root, "basicInfo");
    if(info != NULL) {
        setBasicInfo(&resume, info);
    }

    YamlNode *jobHistoryNode = searchMapping(root, "jobHistory");
    if(jobHistoryNode != NULL) {
        resume.jobHistory = malloc(MAX_JOBS * sizeof(Job));
        resume.numJobs = setJobHistory(resume.jobHistory, jobHistoryNode, MAX_JOBS);
    }

    return resume;
}

void setIfHasMapping(char** storage, YamlNode *node, char* key){
    YamlNode* attrNode;
    attrNode = searchMapping(node, key);
    if(attrNode != NULL) {
        char* val = getVal(attrNode);
        *storage = (char*) malloc(sizeof(char*) * strlen(val));
        strcpy(*storage, val);
    }
}

void jobFromYamlNode(Job *job, YamlNode *jobNode) {

    setIfHasMapping(&job->company, jobNode, "company");
    setIfHasMapping(&job->startDate, jobNode, "startDate");
    setIfHasMapping(&job->endDate, jobNode, "endDate");
    setIfHasMapping(&job->description, jobNode, "description");
    setIfHasMapping(&job->boss, jobNode, "boss");
    setIfHasMapping(&job->contact, jobNode, "contact");
}

int setJobHistory(Job* jobs, YamlNode *jobNode, int arrSize) {
    int count = 0;

    while(count != arrSize && jobNode != NULL) {
        jobFromYamlNode(&jobs[count], jobNode);
        jobNode = getSibling(jobNode);
        count++;
    }

    return count;
}
