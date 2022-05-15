#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "log.h"

typedef void (*TestCase)(int);

START_TEST(test_logger)
{
    ck_assert_int_eq(LOG_ERROR, 5);
}
END_TEST

START_TEST(test_log)
{
    ck_assert_int_eq(LOG_ERROR, 5);
}
END_TEST


static Suite *create_suite(const char *name, int n, ...)
{
    Suite *suite = suite_create(name);

    va_list cases;
    va_start(cases, n);
    for (int i = 0; i < n; i++)
    {
        TestCase c = va_arg(cases, TestCase);

        TCase *tc_core = tcase_create("Core");
        tcase_add_test(tc_core, c);
        suite_add_tcase(suite, tc_core);
    }
    
    va_end(cases);
    return suite;
}

static void final_report(int count, int fails) 
{
    char *icon = fails == 0 ? "✅" : "❌";
    printf("%s  FAILED: %d   TOTAL: %d  \n", icon, fails, count);
    printf("----------------------------------------------------------------------\n");
}

int main(void)
{
    int fail_count = 0;
    int total_count = 0;      

    Suite *suite = create_suite("Terrario", 2, test_logger, test_log);
    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    fail_count = srunner_ntests_failed(runner);
    total_count = srunner_ntests_run(runner);
    srunner_free(runner);
    
    printf("----------------------------------------------------------------------\n");

    final_report(total_count, fail_count);
    return (fail_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}
