#include "test_hooks.h"
#include "terrario/hooks.h"
#include "test.h"

static void *CONSUME = NULL;

/*--------------------------------------------------------------*/
void start_hook(void *args) { CONSUME = args; }
void close_hook(void *args) { CONSUME = args; }

START_TEST(test_hook_into_game_start)
{
    hook_into(TR_GAME_STATE_START, start_hook);
    ck_assert_int_eq(hook_active_count_at(TR_GAME_STATE_START), 1);

    // Reset state.
    hook_clear_from(TR_GAME_STATE_START);
}
END_TEST

START_TEST(test_hook_into_game_close)
{
    hook_into(TR_GAME_STATE_CLOSE, close_hook);
    ck_assert_int_eq(hook_active_count_at(TR_GAME_STATE_CLOSE), 1);


    // Reset state.
    hook_clear_from(TR_GAME_STATE_CLOSE);
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
    hook_into(TR_GAME_STATE_START, boolean_flippin_hook);

    // Hook should flip state.
    hook_run_all_at(TR_GAME_STATE_START);
    ck_assert(boolean_state);

    // Reset state.
    boolean_state = 0;
    hook_clear_from(TR_GAME_STATE_START);
}
END_TEST

START_TEST(test_hooks_are_called_when_state_runs)
{
    hook_into(TR_GAME_STATE_START, boolean_flippin_hook);
    hook_into(TR_GAME_STATE_START, boolean_flippin_hook);

    // Hook should flip state, and second flip it back.
    hook_run_all_at(TR_GAME_STATE_START);
    ck_assert(!boolean_state);

    // Reset state.
    boolean_state = 0;
    hook_clear_from(TR_GAME_STATE_START);
}
END_TEST

START_TEST(test_hooks_storage_must_resize)
{
    int rounds = 10;
    for (int i = 0; i < rounds; i++)
    {
        hook_into(TR_GAME_STATE_START, start_hook);
        PRINTF_TEST("Added hook %d to state: 0x%x", i, TR_GAME_STATE_START);
    }
    ck_assert_int_eq(hook_active_count_at(TR_GAME_STATE_START), rounds);


    // Reset state.
    hook_clear_from(TR_GAME_STATE_START);
}
END_TEST

START_TEST(test_hooks_get_cleared)
{
    for (int i = 0; i < 5; i++)
        hook_into(TR_GAME_STATE_START, start_hook);

    ck_assert_int_eq(0, hook_clear_from(TR_GAME_STATE_START));
    ck_assert_int_eq(0, hook_active_count_at(TR_GAME_STATE_START));

    // Reset state.
}
END_TEST
/*--------------------------------------------------------------*/


void test_hooks_load_cases(Suite *suite)
{
    test_add_case(suite, test_hook_into_game_start);
    test_add_case(suite, test_hook_into_game_close);

    test_add_case(suite, test_hook_is_called_when_state_runs);
    test_add_case(suite, test_hooks_are_called_when_state_runs);

    test_add_case(suite, test_hooks_storage_must_resize);

    test_add_case(suite, test_hooks_get_cleared);
}