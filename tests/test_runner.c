#include <check.h>
#include "resume_test.h"
#include "yaml_test.h"

Suite* money_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Resume");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_load_file);
    tcase_add_test(tc_core, test_simple_yaml_parse);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = money_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
