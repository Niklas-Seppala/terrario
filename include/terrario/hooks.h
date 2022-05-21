#if !defined(HOOKS)
#define HOOKS
#include "terrario/error.h"


// NOTE: Trying to work with single hook function
// prototype. If this does not work for some reason
// fall back to original idea of various hooks for
// different game states.
typedef void (*GameHook)(void*);

typedef enum GAME_STATE {
    GAME_START = 0x1, // NOTE: Increment in power of two -> combined flags.
    GAME_CLOSE = 0x2
    // NOTE: Separate enumerations for rendering mayhaps.
    // NOTE:          --||--       for adding GameObjects and so on.
} GameState;

void hooks_init(void);

RC hook_into(GameState state, GameHook hook);

void hook_run(GameState state);

int hook_active_count(GameState state);

#endif // HOOKS
