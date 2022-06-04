#include <stdlib.h>

#include "debug/log.h"
#include "terrario/hooks.h"
#include "terrario/error.h"


typedef struct hook_collection {
    TR_GameState type;
    TR_GameHook *hooks;
    int count;
    int size_limit;
} TR_HookCollection;


static TR_HookCollection HOOKS_AT_START;
static TR_HookCollection HOOKS_AT_CLOSE;

static void run(TR_HookCollection *state_hooks, void* args)
{
    NOT_NULL(state_hooks);
    for (int i = 0; i < state_hooks->count; i++)
    {
        NOT_NULL(state_hooks->hooks);
        state_hooks->hooks[i](args);
    }
}

static void store_hook(TR_HookCollection *state_hooks, TR_GameHook hook) 
{
    // Allocate space for hooks, if not yet done.
    if (state_hooks->hooks == NULL) 
    {
        state_hooks->hooks = calloc(HOOK_START_CAPACITY, sizeof(TR_GameHook));
        state_hooks->size_limit = HOOK_START_CAPACITY;
    }

    // Make sure we got enough space.
    if (state_hooks->count >= state_hooks->size_limit)
    {
        PRINTF_DEBUG("Hooks for state: 0x%x are at current max capacity: %d",
                     state_hooks->type, state_hooks->size_limit);

        state_hooks->size_limit *= HOOK_CAPACITY_GROWTH;
        state_hooks->hooks = realloc(state_hooks->hooks,
                                     state_hooks->size_limit * sizeof(TR_GameHook));

        PRINTF_DEBUG("New hook capacity for state 0x%x: %d", state_hooks->type,
                      state_hooks->size_limit);
    }
    // Store hook.
    state_hooks->hooks[state_hooks->count++] = hook;
}

static int unstore_hooks(TR_HookCollection *state_hooks)
{
    return state_hooks->count = 0;
}



void hook_into(TR_GameState state, TR_GameHook hook)
{
    int valid_state_provided = 0;
    if (state & TR_GAME_STATE_START)
    {
        store_hook(&HOOKS_AT_START, hook);
        valid_state_provided = 1;
    }
    if (state & TR_GAME_STATE_CLOSE)
    {
        store_hook(&HOOKS_AT_CLOSE, hook);
        valid_state_provided = 1;
    }

    if (!valid_state_provided) 
    {
        PRINTF_ERROR("Unknown game state when registering hook: 0x%x", state);
    }
}

void hook_run_all_at(TR_GameState state) 
{
    switch (state)
    {
    case TR_GAME_STATE_START: run(&HOOKS_AT_START, NULL); break;
    case TR_GAME_STATE_CLOSE: run(&HOOKS_AT_CLOSE, NULL); break;
    default:
        PRINTF_ERROR("Unknown game state when running hooks for state: 0x%x", state);
        break;
    }
}

int hook_active_count_at(TR_GameState state)
{
    switch (state)
    {
    case TR_GAME_STATE_START: return HOOKS_AT_START.count;
    case TR_GAME_STATE_CLOSE: return HOOKS_AT_CLOSE.count;
    default:
        PRINTF_ERROR("Unknown game state when querying hook count: 0x%x",
                     state);
        return INVALID_COUNT;
    }
}

int hook_clear_from(TR_GameState state) 
{
    switch (state)
    {
    case TR_GAME_STATE_START: return unstore_hooks(&HOOKS_AT_START);
    case TR_GAME_STATE_CLOSE: return unstore_hooks(&HOOKS_AT_CLOSE);
    default:
        PRINTF_ERROR("Unknown game state when clearing hooks: 0x%x", state);
        return 0;
    }
}
