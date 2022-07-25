/**
 * @file terrario.h
 * @copyright Copyright (c) 2022
 * @date 2022-06-04
 * @author Niklas Seppälä
 * 
 * @brief General project wide definitions.
 */

#if !defined(GUARD_TERRARIO_H)
#define GUARD_TERRARIO_H

// ---------------- PROJECT OPTIONS --------------- 
#ifndef GAME_NAME
    #define GAME_NAME "Terrario"
#endif

#ifndef TARGET_FPS
    #define TARGET_FPS 60
#endif

#ifndef SCREEN_DIMENSIONS
    #define SCREEN_START_WIDTH 650
    #define SCREEN_START_HEIGHT 650
#endif
// ------------------------------------------------ 


// ---------------- GAME KEYBINDINGS --------------
#define TR_KEY_JUMP            KEY_SPACE
#define TR_KEY_MOVE_UP         KEY_W
#define TR_KEY_MOVE_DOWN       KEY_S
#define TR_KEY_MOVE_LEFT       KEY_A
#define TR_KEY_MOVE_RIGHT      KEY_D

#define TR_KEY_MOUSE_ACTION_1  MOUSE_BUTTON_LEFT
#define TR_KEY_MOUSE_ACTION_2  MOUSE_BUTTON_RIGHT
// ------------------------------------------------

// Empty macro implementation.
#define UNDEFINED_MACRO

// Stringify variable
#define STRINGIFY(x) STRINGIFY_(x)
#define STRINGIFY_(x) #x

/**
 * @brief Basic return codes for this project.
 */
typedef enum return_code {
    TR_ERROR = 0,      // Function error
    TR_SUCCESS = 1     // Function success
} TR_RC;


typedef enum directions {
    TR_NO_DIRECTION = 0x0,
    TR_UP           = 0x1,
    TR_RIGHT        = 0x2,
    TR_DOWN         = 0x4,
    TR_LEFT         = 0x8
} TR_Direction;

#endif // GUARD_TERRARIO_H
