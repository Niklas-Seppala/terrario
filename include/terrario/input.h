/**
 * @file input.h
 * @copyright Copyright (c) 2022
 * @date 2022-06-05
 * @author Niklas Seppälä
 * 
 * @brief Public API for the player inputs. Module works using
 *        opaque pointer to internal input struct. All r/w to
 *        input state should go through API provided here. 
 *        
 *        All reads return copy of that specified field, so input is
 *        immutable for each frame.
 */


#if !defined(GUARD_INPUT_H)
#define GUARD_INPUT_H
#include <stdbool.h>
#include <raylib.h>
#include "terrario.h"

/**
 * @brief Opaque pointer to struct player_input, that
 *        holds player's input.
 * 
 *        Data of thr struct allways only be accessed with
 *        Input API, defined in input.h file.
 */
typedef struct player_input *TR_PlayerInput;

/**
 * @brief Structure that holds player's mouse state.
 */
typedef struct mouse {
    Vector2 world_position;  // Mouse position in the GameWorld.
    Vector2 screen_position; // Mouse position related to the player's camera.
    bool    click;           // Did player click mouse_1 (press -> release).
    bool    down;            // Is mouse_1 button held down.
} TR_PlayerMouse;


/**
 * @brief Allocates HEAP memory for player's input data.
 * 
 * @return TR_PlayerInput Opaque pointer to player's input data.
 */
TR_PlayerInput TR_input_alloc(void);

/**
 * @brief Frees HEAP memory being held by TR_PlayerInput input.
 * 
 * @param input Player's input data for each frame.
 */
void TR_input_free(TR_PlayerInput *input);

/**
 * @brief Read player's inputs for current frame.
 * 
 * @param input Player's input data for each frame.
 */
void TR_input_read(TR_PlayerInput input);

/**
 * @brief Access player's input direction.
 * 
 * @param input Player's input data for each frame.
 * @return TR_DIR 
 */
TR_Direction TR_input_get_player_dir(TR_PlayerInput input);

/**
 * @brief Access player's jump state.
 * 
 * @param input Player's input data for each frame.
 * @return true 
 * @return false 
 */
bool TR_input_get_player_jump(TR_PlayerInput input);

/**
 * @brief Access player's mouse inputs.
 * 
 * @param input Player's input data for each frame.
 * @return TR_PlayerMouse 
 */
TR_PlayerMouse TR_input_get_player_mouse(TR_PlayerInput input);

/**
 * @brief Access player's movement inputs.
 * 
 * @param input Player's input data for each frame.
 * @return Vector2 
 */
Vector2 TR_input_get_player_movement(TR_PlayerInput input);

#ifdef DEBUG
#include <stdio.h>
#define INPUT_STR_LEN 256
/**
 * @brief 
 * 
 * @param input 
 * @param buffer 
 */
char *TR_input_str(TR_PlayerInput input, char *buffer);
#endif

#endif // GUARD_INPUT_H
