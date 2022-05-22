#include "test.h"
#include "test_hooks.h"


Suite *test_add_case(Suite *suite, TestCase tc)
{
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, tc);
    suite_add_tcase(suite, tc_core);
    return suite;
}

int main(void)
{
    int fail_count = 0;
    int total_count = 0;

    Suite *suite = suite_create("Terrario");

    // LOAD HOOK TESTS
    test_hooks_load_cases(suite);

    SRunner *runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    fail_count = srunner_ntests_failed(runner);
    total_count = srunner_ntests_run(runner);
    srunner_free(runner);
    
    printf("----------------------------------------------------------------------\n");
    char *icon = fail_count == 0 ? "✅" : "❌";
    printf("%s  FAILED: %d   TOTAL: %d  \n", icon, fail_count, total_count);
    printf("----------------------------------------------------------------------\n");

    return (fail_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}
