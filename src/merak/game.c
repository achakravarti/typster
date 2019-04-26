#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "merak.h"




struct game {
        merak_game_delegate *update;
        merak_game_delegate *render;
};




static sol_tls struct game *game_inst = SOL_PTR_NULL;


extern sol_erno merak_game_init(merak_game_delegate *update,
                                merak_game_delegate *render)
{
        const int iflag = IMG_INIT_PNG;

SOL_TRY:
        sol_assert (update && render, SOL_ERNO_PTR);
        sol_assert (!game_inst, SOL_ERNO_STATE);

        sol_try (sol_ptr_new((sol_ptr **) &game_inst, sizeof (*game_inst)));
        game_inst->update = update;
        game_inst->render = render;

        sol_assert (SDL_Init(SDL_INIT_EVERYTHING) >= 0, SOL_ERNO_STATE);
        sol_assert ((IMG_Init(iflag) & iflag) == iflag, SOL_ERNO_STATE);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());
        sol_log_error(IMG_GetError());

SOL_FINALLY:
        return sol_erno_get();
}




extern void merak_game_exit(void)
{
        if (sol_likely (game_inst)) {
                sol_ptr_free((sol_ptr **) &game_inst);
                SDL_Quit();
                IMG_Quit();
        }
}




extern sol_erno merak_game_run(void)
{
SOL_TRY:
        sol_assert (game_inst, SOL_ERNO_STATE);

        while (SOL_BOOL_TRUE) {
                sol_try (game_inst->update());
                sol_try (merak_event_update());
                sol_try (merak_arena_update());

                sol_try (game_inst->render());
                sol_try (merak_arena_draw());
                sol_try (merak_screen_render());
        }

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

