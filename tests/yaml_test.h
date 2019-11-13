#ifndef YAML_TEST
#define YAML_TEST

#include <stdio.h>
#include <stdlib.h>
#include "resume_yaml.h"
#include <check.h>

START_TEST (test_simple_yaml_parse)
{
    int PAIRS = 2;
    int yamlSize;
    char* header = "%YAML 1.1\n---\n";
    const char* keys[PAIRS];
    const char* vals[PAIRS];
    keys[0] = "name";
    vals[0] = "collin";

    keys[1] = "profession";
    vals[1] = "cyberneticist";

    yamlSize = strlen(header);
    for(int i = 0; i < PAIRS; i++) {
        yamlSize += strlen(keys[i]);
        yamlSize += strlen(vals[i]);

        //" :" & "\n" in "key: val\n"
        yamlSize += 3;
    }

    char* aYaml = malloc(sizeof(char) * yamlSize);

    strcpy(aYaml, header);
    for(int i = 0; i < PAIRS; i++) {
        strcat(aYaml, keys[i]);
        strcat(aYaml, ": ");
        strcat(aYaml, vals[i]);
        strcat(aYaml, "\n");
    }


    YamlParser *parser = newYamlParser(aYaml);
    for(int i = 0; i < PAIRS; i++) {
        YamlNode node = nextNode(parser);
        ck_assert_str_eq(node.key, keys[i]);
        ck_assert_str_eq(node.val, vals[i]);
    }
    freeYamlParser(parser);
}
END_TEST

START_TEST (test_yaml_node_set_and_get_val) {
    YamlNode node;
    char dat[] = "foobar";
    char expected[strlen(dat)];
    strcpy(expected, dat);

    setVal(&node, dat);

    //Ensure strcpy in setStrVal
    dat[2] = 'z';
    ck_assert_str_eq(getVal(&node), expected);
}
END_TEST

START_TEST(test_yaml_node_set_and_get_child) {
    YamlNode parent;
    YamlNode child;
    YamlNode *actual, *expected;

    setChild(&parent, &child);


    expected = &child;
    actual = getChild(&parent);
    ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_yaml_node_set_and_get_sibling) {
    YamlNode node;
    YamlNode sibling;
    YamlNode *actual, *expected;

    setSibling(&node, &sibling);


    expected = &sibling;
    actual = getSibling(&node);
    ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_yaml_list) {
    char* listYaml =
        "%YAML 1.1\n---\n"\
        "a: \n"\
        " - b\n"\
        " - c\n"\
        " - d\n";

    YamlParser *parser = newYamlParser(listYaml);
    YamlNode *parsed = parseAll(parser);

    ck_assert_str_eq(getVal(parsed), "a");

    parsed = getChild(parsed);
    ck_assert_str_eq(getVal(parsed), "b");

    parsed = getSibling(parsed);
    ck_assert_str_eq(getVal(parsed), "c");

    parsed = getSibling(parsed);
    ck_assert_str_eq(getVal(parsed), "d");
}
END_TEST
#endif
