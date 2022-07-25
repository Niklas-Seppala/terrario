#include <stdlib.h>
#include <string.h>
#include <raylib.h>

#include "terrario.h"
#include "terrario/input.h"
#include "terrario/error.h"

#define MOVEMENT_ACTIVE (1)

struct player_input 
{
    Vector2 movement;
    TR_PlayerMouse mouse;
    TR_Direction direction;
    bool jump;
};

TR_PlayerInput TR_input_alloc(void)
{
    TR_PlayerInput input = malloc(sizeof(struct player_input));
    NOT_NULL(input);

    return input;
}

void TR_input_free(TR_PlayerInput *input)
{
    NOT_NULL(input);
    NOT_NULL(*input);
    free(*input);
    *input = NULL;
}

void TR_input_read(TR_PlayerInput input)
{
    NOT_NULL(input);

    // Clear state.
    memset(input, 0, sizeof(struct player_input));

    // Vertical movement sum.
    if (IsKeyDown(TR_KEY_MOVE_UP))
    {
        input->movement.y += MOVEMENT_ACTIVE;
    }
    if (IsKeyDown(TR_KEY_MOVE_DOWN))
    {
        input->movement.y -= MOVEMENT_ACTIVE;
    }

    // Horizontal movement sum.
    if (IsKeyDown(TR_KEY_MOVE_RIGHT))
    {
        input->movement.x += MOVEMENT_ACTIVE;
    }
    if (IsKeyDown(TR_KEY_MOVE_LEFT))
    {
        input->movement.x -= MOVEMENT_ACTIVE;
    }

    // Mouse state.
    input->mouse.click = IsMouseButtonPressed(TR_KEY_MOUSE_ACTION_1);
    input->mouse.down  = IsMouseButtonDown(TR_KEY_MOUSE_ACTION_1);
    input->mouse.world_position = GetMousePosition();
    // TODO: Screen position.

    input->jump = IsKeyDown(TR_KEY_JUMP);

}

inline TR_Direction TR_input_get_player_dir(TR_PlayerInput input)
{
    NOT_NULL(input);
    return input->direction;
}

inline bool TR_input_get_player_jump(TR_PlayerInput input)
{
    NOT_NULL(input);
    return input->jump;
}

inline TR_PlayerMouse TR_input_get_player_mouse(TR_PlayerInput input)
{
    NOT_NULL(input);
    return input->mouse;
}

inline Vector2 TR_input_get_player_movement(TR_PlayerInput input)
{
    NOT_NULL(input);
    return input->movement;
}

char *TR_input_str(TR_PlayerInput input, char *buffer)
{
    NOT_NULL(input);
    NOT_NULL(buffer);

    snprintf(buffer, INPUT_STR_LEN,
        "MOV: (%.3f, %.3f) JMP: %d",
        input->movement.x, input->movement.y,
        input->jump);
    return buffer;
}