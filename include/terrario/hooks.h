/**
 * @file log.h
 * @copyright Copyright (c) 2022
 * @date 2022-06-04
 * @author Niklas Seppälä
 * 
 * @brief 
 */

#if !defined(HOOKS_H)
#define HOOKS_H
#include "terrario.h"
#include "terrario/error.h"


// NOTE: Trying to work with single hook function
// prototype. If this does not work for some reason
// fall back to original idea of various hooks for
// different game states.
/**
 * @brief 
 * 
 */
typedef void (*GameHook)(void*);

/**
 * @brief asdasd
 * 
 */
typedef enum GAME_STATE {
    GAME_START = 0x1, // NOTE: Increment in power of two -> combined flags.
    GAME_CLOSE = 0x2
    // NOTE: Separate enumerations for rendering mayhaps.
    // NOTE:          --||--       for adding GameObjects and so on.
} GameState;

/**
 * @brief 
 * 
 */
void hooks_init(void);

/**
 * @brief 
 * 
 * @param state 
 * @param hook 
 * @return TER_RC 
 */
TER_RC hook_into(GameState state, GameHook hook);

/**
 * @brief 
 * 
 * @param state 
 */
void hook_run_all_at(GameState state);

/**
 * @brief 
 * 
 * @param state 
 * @return int 
 */
int hook_active_count(GameState state);

#endif // HOOKS_H
