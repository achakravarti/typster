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




extern sol_erno merak_keyboard_state(const MERAK_KEYBOARD_KEY key,
                                     MERAK_KEYBOARD_STATE *state)
{
SOL_TRY:
        sol_assert (key_states, SOL_ERNO_STATE);
        sol_assert (state, SOL_ERNO_PTR);

        *state = key_states[key];

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

