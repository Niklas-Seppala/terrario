#include "terrario/hooks.h"
#include <stdlib.h>
#include "debug/log.h"
#include "terrario/error.h"

#define HOOK_CAPACITY 128

typedef struct hook_collection {
    GameState type;
    GameHook *hooks;
    GameHook *next_empty;
    int count;
} HookArray;


static HookArray AT_START;
static HookArray AT_CLOSE;

static void run(HookArray *storage, void* args)
{
    NOT_NULL(storage);
    for (int i = 0; i < storage->count; i++)
    {
        NOT_NULL(storage->hooks);
        storage->hooks[i](args);
    }
}

static TER_RC try_store_hook(HookArray *storage, GameHook hook) 
{
    // Allocate space for hooks.
    if (storage->hooks == NULL) 
    {
        storage->hooks = calloc(HOOK_CAPACITY, sizeof(GameHook));
        storage->next_empty = storage->hooks;
    }

    // Store if got space.
    if (storage->next_empty == NULL) 
    {
        PRINTF_ERROR("%s", "Hook array is full.");
        return TER_ERROR;
    }
    *storage->next_empty = hook;
    storage->count++;
    
    // Check capacity, if full return;
    if (storage->count == HOOK_CAPACITY)
    {
        log_printf(LOG_WARNING, "Hook array at max capacity!");
        return TER_SUCCESS;
    }

    // Move to next slot next slot.
    storage->next_empty++;

    return TER_SUCCESS;
}

TER_RC hook_into(GameState state, GameHook hook)
{
    TER_RC status;
    switch (state)
    {
    case GAME_START:
        status = try_store_hook(&AT_START, hook);
        break;
    case GAME_CLOSE:
        status = try_store_hook(&AT_CLOSE, hook);
        break;
    default:
        PRINTF_ERROR("%s 0x%x", "Unknown game state when registering hook:", state);
        status = TER_ERROR;
        break;
    }
    return status;
}

void hook_run_all_at(GameState state) 
{
    switch (state)
    {
    case GAME_START:
        run(&AT_START, NULL);
        break;
    case GAME_CLOSE:
        run(&AT_CLOSE, NULL);
        break;
    default:
        break;
    }
}

int hook_active_count(GameState state)
{
    switch (state)
    {
    case GAME_START: return AT_START.count;
    case GAME_CLOSE: return AT_CLOSE.count;
    default:         return INVALID_COUNT;
    }
}