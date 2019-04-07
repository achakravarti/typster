#include <SDL2/SDL.h>
#include <stdlib.h>
#include "marek.h"




struct game {
        marek_game_delegate *input;
        marek_game_delegate *update;
        marek_game_delegate *render;
};




static sol_tls struct game *game_inst = SOL_PTR_NULL;




extern sol_erno marek_game_init(marek_game_delegate *input,
                                marek_game_delegate *update,
                                marek_game_delegate *render)
{
SOL_TRY:
        sol_assert (input && update && render, SOL_ERNO_PTR);
        sol_assert (!game_inst, SOL_ERNO_STATE);

        sol_try (sol_ptr_new((sol_ptr **) &game_inst, sizeof (*game_inst)));
        game_inst->input = input;
        game_inst->update = update;
        game_inst->render = render;

        sol_assert (SDL_Init(SDL_INIT_EVERYTHING) >= 0, SOL_ERNO_STATE);
        sol_try (marek_screen_init());
        sol_try (marek_event_init());

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}




extern void marek_game_exit(void)
{
        if (sol_likely (game_inst)) {
                SDL_Quit();
                marek_screen_exit();
                marek_event_exit();

                sol_ptr_free((sol_ptr **) &game_inst);
                exit(SOL_ERNO_NULL);
        }
}




extern sol_erno marek_game_run(void)
{
SOL_TRY:
        sol_assert (game_inst, SOL_ERNO_STATE);

        while (SOL_BOOL_TRUE) {
                sol_try (game_inst->input());
                sol_try (game_inst->update());
                sol_try (game_inst->render());
        }

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

