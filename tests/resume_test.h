#ifndef RESUME_TEST
#define RESUME_TEST

#include <stdio.h>
#include <stdlib.h>
#include "resume.h"
#include "resume_yaml.h"
#include <check.h>

void writeTestFile(char* filePath, char* testStr) {
    FILE* f;
    f = fopen(filePath, "w");
    fprintf(f, "%s", testStr);
    fclose(f);
}

START_TEST (test_load_file)
{
    char* filePath = "./data/testLoadFileData";
    char* result = (char*) malloc(15);
    char expected[] = "abcd\n";

    writeTestFile(filePath, expected);
    loadFile(result, filePath);
    ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST (test_read_basic_info)
{
    char* basic_info =
        "basicInfo:\n"\
        "  name: Collin Bell\n"\
        "  birthdate: 1992-01-15\n"\
        "  location: St Louis, MO\n"\
        "  mtbi: INTJ\n";

    Resume resume = resumeFromYaml(basic_info);

    ck_assert_str_eq(resume.basicInfo.name, "Collin Bell");
    ck_assert_str_eq(resume.basicInfo.birthday, "1992-01-15");
    ck_assert_str_eq(resume.basicInfo.location, "St Louis, MO");
    ck_assert_str_eq(resume.basicInfo.mtbi, "INTJ");
}
END_TEST

START_TEST (test_read_job_history)
{
    YamlParser *parser;
    YamlNode *resumeRootNode;

    char* jobYaml =
        "jobHistory:\n"\
        "  - company: Trademark Ads\n"\
        "    startDate: 2015-01\n"\
        "    endDate: 2016-06\n"\
        "    description: I wrote beckend features for hospitaljobsonline.com, developed an internal project management system from scratch, and I also helped to develop a real estate web app. We used Linux, PHP, MySql, JQuery, and Solr.\n"\
        "    boss: George Corley\n"\
        "    contact: 865-966-1690\n"\

        "  - company: Oak Ridge National Lab\n"\
        "    startDate: 2013-01\n"\
        "    endDate: 2013-08\n"\
        "    description: I built a GIS social media visualization tool in Java. I also built a back end system for passing internal network security data to another intern's vizualizations\n"\
        "    boss: Chad Steed\n"\
        "    contact: csteed@acm.org\n";


    Resume resume = resumeFromYaml(jobYaml);

    ck_assert_str_eq(resume.jobHistory[0].company, "Trademark Ads");
    ck_assert_str_eq(resume.jobHistory[0].startDate, "2015-01");
    ck_assert_str_eq(resume.jobHistory[0].endDate, "2016-06");

    ck_assert_str_eq(resume.jobHistory[1].description, "I built a GIS social media visualization tool in Java. I also built a back end system for passing internal network security data to another intern's vizualizations");
    ck_assert_str_eq(resume.jobHistory[1].boss, "Chad Steed");
    ck_assert_str_eq(resume.jobHistory[1].contact, "csteed@acm.org");
}
END_TEST
#endif
