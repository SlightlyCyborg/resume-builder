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
#endif
