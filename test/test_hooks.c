#include "test_hooks.h"
#include "terrario/hooks.h"

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
static int boolean_state = 0;
void boolean_flippin_hook(void *args) 
{ 
    CONSUME = args;
    boolean_state = !boolean_state;
}

START_TEST(test_hook_is_called_when_state_runs)
{
    hook_into(GAME_START, boolean_flippin_hook);

    // Hook should flip state.
    hook_run_all_at(GAME_START);
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
    hook_run_all_at(GAME_START);
    ck_assert(!boolean_state);

    // Reset state;
    boolean_state = 0;
}
END_TEST
/*--------------------------------------------------------------*/


void test_hooks_load_cases(Suite *suite)
{
    test_add_case(suite, test_hook_into_game_start);
    test_add_case(suite, test_hook_into_game_close);

    test_add_case(suite, test_hook_is_called_when_state_runs);
    test_add_case(suite, test_hooks_are_called_when_state_runs);
}