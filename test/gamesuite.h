#if !defined(GUARD_GAMESUITE_H)
#define GUARD_GAMESUITE_H
#include "terrario.h"
#include "debug/log.h"
#include <raylib.h>

#define GAMESUITE_START(window_id) InitWindow(SCREEN_START_WIDTH, SCREEN_START_HEIGHT, window_id); \
                        SetTargetFPS(TARGET_FPS);

#define GAMESUITE_DRAW while (!WindowShouldClose()) \
                      { \
                      BeginDrawing();

#define GAMESUITE_DRAW_END EndDrawing(); \
                      } \

#define GAMESUITE_END CloseWindow();

#define GAMSUITE_REQUEST_EXIT SIMULATE_KEY_PRESS("Escape")

#define GAMESUITE_EXIT_WHEN(cond) if (cond) {GAMSUITE_REQUEST_EXIT;}

#endif // GUARD_GAMESUITE_H
