#ifndef RESUME_TEST
#define RESUME_TEST

#include <stdio.h>
#include <stdlib.h>
#include "resume.h"
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
#endif
