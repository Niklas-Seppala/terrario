#include <raylib.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "debug/log.h"
#include "terrario/hooks.h"
#include "terrario.h"


void *b = NULL;
static void asd(void *asd) {
    b = asd;
    printf("MOI\n");
}

int main(void)
{
    log_setup();

    hook_into(GAME_START, asd);
    
    InitWindow(SCREEN_START_WIDTH, SCREEN_START_HEIGHT, GAME_NAME);
    SetTargetFPS(TARGET_FPS);


    run_hooks(GAME_START);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    log_teardown();

    return EXIT_SUCCESS;
}
