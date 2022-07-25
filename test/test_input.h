#if !defined(GUARD_TEST_INPUT_H)
#define GUARD_TEST_INPUT_H
#include "test.h"

#define SIMULATE_KEY_DOWN(KEY_CODE) system("xdotool keydown " KEY_CODE);

#define SIMULATE_KEY_PRESS(KEY_CODE) system("xdotool key " KEY_CODE);

void test_input_load_cases(Suite *suite);

#define TEST_KEY_JUMP            "Space"
#define TEST_KEY_MOVE_UP         "W"
#define TEST_KEY_MOVE_DOWN       "S"
#define TEST_KEY_MOVE_LEFT       "A"
#define TEST_KEY_MOVE_RIGHT      "D"

#endif // GUARD_TEST_INPUT_H
