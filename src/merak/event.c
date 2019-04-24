#include <SDL2/SDL.h>
#include "merak.h"




#define EVENT_COUNT 3




static sol_tls SOL_BOOL event_init = SOL_BOOL_FALSE;




static sol_inline void event_exit(void)
{
        merak_screen_exit();
        merak_keyboard_exit();
        merak_event_exit();
        merak_arena_exit();
        merak_game_exit();
}




extern sol_erno merak_event_init(void)
{
        event_init = SOL_BOOL_TRUE;
        return SOL_ERNO_NULL;
}




extern void merak_event_exit(void)
{
        event_init = SOL_BOOL_FALSE;
}




extern sol_erno merak_event_update(void)
{
        auto SDL_Event event;

SOL_TRY:
        sol_assert (event_init, SOL_ERNO_STATE);

        while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                        event_exit();
                        break;

                case SDL_KEYUP:
                        sol_try (merak_keyboard_update());
                        break;

                case SDL_KEYDOWN:
                        sol_try (merak_keyboard_update());
                        break;

                default:
                        break;
                }
        }

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

