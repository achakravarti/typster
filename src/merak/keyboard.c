#include "merak.h"
#include <SDL2/SDL.h>




static sol_tls const sol_u8 *key_states = SOL_PTR_NULL;




extern sol_erno merak_keyboard_init(void)
{
SOL_TRY:
        sol_assert (!key_states, SOL_ERNO_STATE);

        key_states = SDL_GetKeyboardState(SOL_PTR_NULL);
        sol_assert (key_states, SOL_ERNO_STATE);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void merak_keyboard_exit(void)
{
        key_states = SOL_PTR_NULL;
}




extern sol_erno merak_keyboard_up(MERAK_KEYBOARD_KEY key, SOL_BOOL *up)
{
SOL_TRY:
        sol_assert (key_states, SOL_ERNO_STATE);
        sol_assert (up, SOL_ERNO_PTR);

        *up = key_states[key] == 0;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_keyboard_down(MERAK_KEYBOARD_KEY key, SOL_BOOL *down)
{
SOL_TRY:
        sol_assert (key_states, SOL_ERNO_STATE);
        sol_assert (down, SOL_ERNO_PTR);

        *down = key_states[key] == 1;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_keyboard_update(void)
{
SOL_TRY:
        sol_assert (key_states, SOL_ERNO_STATE);

        key_states = SDL_GetKeyboardState(SOL_PTR_NULL);
        sol_assert (key_states, SOL_ERNO_STATE);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

