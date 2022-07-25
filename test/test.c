#include "test.h"
#include "test_hooks.h"
#include "test_input.h"
#include "test_algorithm.h"

#include "../include/debug/log.h"

#define SUCCESS_DIVIDER TERM_GRN "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" COLOR_RESET
#define FAILURE_DIVIDER TERM_RED "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" COLOR_RESET

Suite *test_add_case(Suite *suite, TestCase tc)
{
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, tc);
    suite_add_tcase(suite, tc_core);
    return suite;
}

int main(void)
{
    log_setup();
    int fail_count = 0;
    int total_count = 0;

    Suite *suite = suite_create("Terrario");

    // Load test which don't utilize gamesuite.
    #ifndef TESTS_W_WINDOW
        test_hooks_load_cases(suite);
        test_linked_list_load_cases(suite);
    #else
        test_input_load_cases(suite);
    #endif

    SRunner *runner = srunner_create(suite);


    srunner_run_all(runner, CK_NORMAL);
    fail_count = srunner_ntests_failed(runner);
    total_count = srunner_ntests_run(runner);
    srunner_free(runner);

    const int success = fail_count == 0;
    const char *DIVIDER = success ? SUCCESS_DIVIDER : FAILURE_DIVIDER;

    printf("\n%s", DIVIDER);
    printf("    %.1f%%    🧪 TOTAL RUN: %d    ✅ PASSED: %d    ❌ FAILED: %d\n",
           (double)total_count / (double)(total_count - fail_count) * 100.0,
           total_count, 
           total_count - fail_count, fail_count);
    
    printf("%s", DIVIDER);

    log_teardown();
    return (fail_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}
