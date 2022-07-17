// #include <X11/Xlib.h>
// #include <X11/extensions/XTest.h>

#include "test_input.h"

void *CONSUME = NULL;

void test_input_load_cases(Suite *suite)
{
    CONSUME = suite;
    // test_add_case(suite, test_hook_into_game_start);
}