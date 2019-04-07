#include <SDL2/SDL.h>
#include "marek/marek.h"




        /* handles the input for a frame */
sol_erno input(void)
{
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                        marek_game_exit();
                        break;

                default:
                        break;
                }
        }

        return SOL_ERNO_NULL;
}


        /* updates the state of a frame */
sol_erno update(void)
{
        auto marek_shade *shade = SOL_PTR_NULL;

SOL_TRY:
        sol_try (marek_shade_spawn(&shade, 96, 128, 128, 256));
        sol_try (marek_screen_clear(shade));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        marek_shade_kill(&shade);
        return sol_erno_get();
}


        /* renders a frame */
sol_erno render(void)
{
SOL_TRY:
        sol_try (marek_screen_render());

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}


int main(int argc, char *argv[])
{
SOL_TRY:
                /* cast arguments to void as we don't use them */
        (void) argc;
        (void) argv;

        sol_try (marek_game_init(&input, &update, &render));
        sol_try (marek_game_run());

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        marek_game_exit();
        return (int) sol_erno_get();
}

