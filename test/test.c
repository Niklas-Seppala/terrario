#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "terrario/hooks.h"

typedef void (*TestCase)(int);

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


static void *CONSUME = NULL;

/*--------------------------------------------------------------*/
void start_hook(void *args) { CONSUME = args; }
void close_hook(void *args) { CONSUME = args; }

START_TEST(test_hook_into_game_start)
{
    hook_into(GAME_START, start_hook);
    ck_assert_int_eq(hook_active_count(GAME_START), 1);
}
END_TEST

START_TEST(test_hook_into_game_close)
{
    hook_into(GAME_CLOSE, close_hook);
    ck_assert_int_eq(hook_active_count(GAME_CLOSE), 1);
}
END_TEST
/*--------------------------------------------------------------*/


/*--------------------------------------------------------------*/
int boolean_state = 0;
void boolean_flippin_hook(void *args) 
{ 
    CONSUME = args;
    boolean_state = !boolean_state;
}

START_TEST(test_hook_is_called_when_state_runs)
{
    hook_into(GAME_START, boolean_flippin_hook);

    // Hook should flip state.
    hook_run(GAME_START);
    ck_assert(boolean_state);

    // Reset state;
    boolean_state = 0;
}
END_TEST

START_TEST(test_hooks_are_called_when_state_runs)
{
    hook_into(GAME_START, boolean_flippin_hook);
    hook_into(GAME_START, boolean_flippin_hook);

    // Hook should flip state, and second flip it back.
    hook_run(GAME_START);
    ck_assert(!boolean_state);

    // Reset state;
    boolean_state = 0;
}
END_TEST
/*--------------------------------------------------------------*/



int main(void)
{
    int fail_count = 0;
    int total_count = 0;      

    Suite *suite = create_suite("Terrario", 4, // Hooks are added to specified game states.
                                               test_hook_into_game_start,
                                               test_hook_into_game_close,

                                               // Hooks are actually ran when game state calls them.
                                               test_hook_is_called_when_state_runs,
                                               test_hooks_are_called_when_state_runs);

    SRunner *runner = srunner_create(suite);
    
    srunner_run_all(runner, CK_NORMAL);
    fail_count = srunner_ntests_failed(runner);
    total_count = srunner_ntests_run(runner);
    srunner_free(runner);
    
    printf("----------------------------------------------------------------------\n");

    final_report(total_count, fail_count);
    return (fail_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}
