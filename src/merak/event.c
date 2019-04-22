#include <SDL2/SDL.h>
#include "merak.h"




extern sol_erno merak_event_init(void)
{
        return SOL_ERNO_NULL;
}




extern void merak_event_exit(void)
{
}




extern sol_erno merak_event_update(void)
{
        auto SDL_Event event;
        auto sol_int more;

SOL_TRY:
        more = SDL_PollEvent(&event);

        while (more) {
                switch (event.type) {
                case SDL_QUIT:
                        merak_screen_exit();
                        merak_keyboard_exit();
                        merak_event_exit();
                        merak_game_exit();
                        break;

                case SDL_KEYUP:
                case SDL_KEYDOWN:
                        sol_try (merak_keyboard_update());
                        break;

                default:
                        break;
                }

                more = SDL_PollEvent(&event);
        }

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

