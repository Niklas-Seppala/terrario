#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "terrario/collections/array-list.h"
#include "debug/log.h"
#include "terrario.h"
#include "terrario/hooks.h"
#include "terrario/input.h"

#define thread_local __thread

int main(void)
{
    log_setup();

    TR_ArrayList list = TR_array_list_alloc();

    int a, b;
    a = 1;
    b = 2;
    TR_array_list_append(list, &a);
    TR_array_list_append(list, &b);

    printf("%d\n", *((int*)TR_array_list_get(list, 1)));

    TR_array_list_remove(NULL, 1);

    // InitWindow(SCREEN_START_WIDTH, SCREEN_START_HEIGHT, GAME_NAME);
    // SetTargetFPS(TARGET_FPS);

    // hook_run_all_at(TR_GAME_STATE_START);
    // while (!WindowShouldClose())
    // {
    //     BeginDrawing();
    //         ClearBackground(BLACK);
    //     EndDrawing();
    // }
    // CloseWindow();
    // hook_run_all_at(TR_GAME_STATE_CLOSE);

    // log_teardown();

    return EXIT_SUCCESS;
}
