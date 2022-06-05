#include <raylib.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "debug/log.h"

#include "terrario.h"
#include "terrario/hooks.h"
#include "terrario/input.h"

int main(void)
{
    log_setup();

    InitWindow(SCREEN_START_WIDTH, SCREEN_START_HEIGHT, GAME_NAME);
    SetTargetFPS(TARGET_FPS);

    hook_run_all_at(TR_GAME_STATE_START);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    hook_run_all_at(TR_GAME_STATE_CLOSE);

    log_teardown();

    return EXIT_SUCCESS;
}
