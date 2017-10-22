#ifndef __CHECK_MACROS_H
#define __CHECK_MACROS_H

#define START_CHECK_MAIN(name) \
    int main() \
    { \
        int number_failed; \
        SRunner *srun = srunner_create(NULL); \
        Suite *suite = suite_create( #name "_suite" ); \
        \
        srunner_add_suite(srun, suite); \
        srunner_set_log(srun, "check_" #name ".log" );

#define CREATE_TEST_CASE(tcname) \
        TCase *tc_##tcname = tcase_create( #tcname ); \
        suite_add_tcase(suite, tc_##tcname )

#define ADD_TEST(tcname, tname) \
        tcase_add_test( tc_##tcname , tname )

#define END_CHECK_MAIN \
        srunner_run_all(srun, CK_VERBOSE); \
        number_failed = srunner_ntests_failed(srun); \
        srunner_free(srun); \
        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE; \
    }

#endif
