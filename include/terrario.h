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


// Empty macro implementation.
#define UNDEFINED_MACRO

// Stringify variable
#define STRINGIFY(x) STRINGIFY_(x)
#define STRINGIFY_(x) #x

/**
 * @brief Basic return codes for this project.
 */
typedef enum return_code {
    TER_ERROR = 0,      // Function error
    TER_SUCCESS = 1     // Function success
} TER_RC;


#endif // GUARD_TERRARIO_H
