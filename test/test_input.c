#include <raylib.h>
#include <unistd.h>
#include "terrario/input.h"
#include "test_input.h"
#include "gamesuite.h"
#include "terrario.h"

START_TEST(test_move_up)
{
    int current_frame = 0;
    TR_PlayerInput input = TR_input_alloc();
    Vector2 movement;

    GAMESUITE_START("Test TR_KEY_MOVE_UP")
        GAMESUITE_DRAW
            SIMULATE_KEY_DOWN(TEST_KEY_MOVE_UP)
            TR_input_read(input);
            GAMESUITE_EXIT_WHEN(current_frame++ > TARGET_FPS);
        GAMESUITE_DRAW_END
    GAMESUITE_END

    movement = TR_input_get_player_movement(input);
    #ifdef DEBUG
        char s[INPUT_STR_LEN];
        PRINTF_TEST("TR_KEY_MOVE_UP: %s", TR_input_str(input, s));
    #endif
    ck_assert_int_gt((int)movement.y, 0);
    ck_assert_int_eq((int)movement.x, 0);

    TR_input_free(&input);
}
END_TEST

START_TEST(test_move_down)
{
    int current_frame = 0;
    TR_PlayerInput input = TR_input_alloc();
    Vector2 movement;

    GAMESUITE_START("Test TR_KEY_MOVE_DOWN")
        GAMESUITE_DRAW
            SIMULATE_KEY_DOWN(TEST_KEY_MOVE_DOWN)
            TR_input_read(input);
            GAMESUITE_EXIT_WHEN(current_frame++ > TARGET_FPS);
        GAMESUITE_DRAW_END
    GAMESUITE_END

    movement = TR_input_get_player_movement(input);

    #ifdef DEBUG
        char s[INPUT_STR_LEN];
        PRINTF_TEST("TR_KEY_MOVE_DOWN: %s", TR_input_str(input, s));
    #endif

    ck_assert_int_lt((int)movement.y, 0);
    ck_assert_int_eq((int)movement.x, 0);

    TR_input_free(&input);
}
END_TEST

START_TEST(test_move_right)
{
    int current_frame = 0;
    TR_PlayerInput input = TR_input_alloc();
    Vector2 movement;

    GAMESUITE_START("Test TR_KEY_MOVE_RIGHT")
        GAMESUITE_DRAW
            SIMULATE_KEY_DOWN(TEST_KEY_MOVE_RIGHT)
            TR_input_read(input);
            GAMESUITE_EXIT_WHEN(current_frame++ > TARGET_FPS);
        GAMESUITE_DRAW_END
    GAMESUITE_END

    movement = TR_input_get_player_movement(input);

    #ifdef DEBUG
        char s[INPUT_STR_LEN];
        PRINTF_TEST("TR_KEY_MOVE_RIGHT: %s", TR_input_str(input, s));
    #endif

    ck_assert_int_gt((int)movement.x, 0);
    ck_assert_int_eq((int)movement.y, 0);

    TR_input_free(&input);
}
END_TEST

START_TEST(test_move_left)
{
    log_setup();
    int current_frame = 0;
    TR_PlayerInput input = TR_input_alloc();
    Vector2 movement;

    GAMESUITE_START("Test TR_KEY_MOVE_LEFT")
        GAMESUITE_DRAW
            SIMULATE_KEY_DOWN(TEST_KEY_MOVE_LEFT)
            TR_input_read(input);
            GAMESUITE_EXIT_WHEN(current_frame++ > TARGET_FPS);
        GAMESUITE_DRAW_END
    GAMESUITE_END

    movement = TR_input_get_player_movement(input);

    #ifdef DEBUG
        char s[INPUT_STR_LEN];
        PRINTF_TEST("TR_KEY_MOVE_LEFT: %s", TR_input_str(input, s));
    #endif

    ck_assert_int_lt((int)movement.x, 0);
    ck_assert_int_eq((int)movement.y, 0);

    TR_input_free(&input);
    log_teardown();
}
END_TEST

void test_input_load_cases(Suite *suite)
{
    // Window tests
    #ifdef TESTS_W_WINDOW
    test_add_case(suite, test_move_up);
    test_add_case(suite, test_move_down);
    test_add_case(suite, test_move_right);
    test_add_case(suite, test_move_left);
    #endif
}
