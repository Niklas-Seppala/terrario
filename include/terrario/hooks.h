/**
 * @file hooks.h
 * @copyright Copyright (c) 2022
 * @date 2022-06-04
 * @author Niklas Seppälä
 * 
 * @brief Provides API to hook into game's states. Hooks
 *        registered to each game state are called in registration
 *        order. Hook it self is just a a function 
 *        pointer of TR_GameHook type.
 * 
 *        Hooks receive void pointer as an argument, and the contents
 *        of that dependends on game state.
 *              TODO: List game state arguments here.
 */


#if !defined(GUARD_HOOKS_H)
#define GUARD_HOOKS_H
#include "terrario.h"
#include "terrario/error.h"


#ifndef HOOK_CG
    #define HOOK_CAPACITY_GROWTH  2
#else
    #define HOOK_CAPACITY_GROWTH  HOOK_CG
#endif

#ifndef HOOKS_SC
    #define HOOK_START_CAPACITY 64
#else
    #define HOOK_START_CAPACITY HOOKS_SC
#endif

/**
 * @brief Hook function pointer type. Hooks should return
 *        void, and they receive void pointer as an argument,
 *        which depends on registered game state.
 * 
 */
typedef void (*TR_GameHook)(void*);

/**
 * @brief Game states where hooks are allowed. Can act as
 *        flags and be combined.
 * 
 */
typedef enum GAME_STATE {
    TR_GAME_STATE_START  = 0x1, // NOTE: Increment in power of two -> combined flags.
    TR_GAME_STATE_CLOSE  = 0x2,
    // TODO: Separate enumerations for rendering mayhaps.
    //                --||--       for adding GameObjects and so on.
} TR_GameState;

/**
 * @brief Attaches hook into specified game state. Hook function
 *        gets called when all hooks are ran for the game state.
 * 
 * @param state Game state where hooks are allowed.
 * @param hook Hook function pointer.
 * @return TER_RC 
 */
void hook_into(TR_GameState state, TR_GameHook hook);

/**
 * @brief Runs all hooks registered to specified game state.
 * 
 * @param state Game state where hooks are allowed.
 */
void hook_run_all_at(TR_GameState state);

/**
 * @brief Get the current active hook count for specified game state.
 * 
 * @param state Game state where hooks are allowed.
 * @return int Current number of hooks at specified game state.
 */
int hook_active_count_at(TR_GameState state);

/**
 * @brief Clears all hooks from specified game state.
 * 
 * @param state Game state where hooks are allowed.
 * @return int Current number of hooks at specified game state.
 */
int hook_clear_from(TR_GameState state);

#endif // GUARD_HOOKS_H
