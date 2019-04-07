#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "marek.h"




struct screen {
        SDL_Renderer *renderer;
        SDL_Window *window;
};




static sol_tls struct screen *screen_inst = SOL_PTR_NULL;




extern sol_erno marek_screen_init(void)
{
        const int wflag = 0;
        const int rflag = SDL_RENDERER_ACCELERATED;
        const int width = 1280;
        const int height = 720;

SOL_TRY:
        sol_assert (!screen_inst, SOL_ERNO_STATE);

        sol_try (sol_ptr_new((sol_ptr **) &screen_inst, sizeof (*screen_inst)));

        screen_inst->window = SDL_CreateWindow("Typster",
                                               SDL_WINDOWPOS_UNDEFINED,
                                               SDL_WINDOWPOS_UNDEFINED,
                                               width,
                                               height,
                                               wflag);
        sol_assert (screen_inst->window, SOL_ERNO_STATE);

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        screen_inst->renderer = SDL_CreateRenderer(screen_inst->window,
                                                   -1,
                                                   rflag);
        sol_assert (screen_inst->renderer, SOL_ERNO_STATE);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}




extern void marek_screen_exit(void)
{
        if (sol_likely (screen_inst)) {
                SDL_DestroyRenderer(screen_inst->renderer);
                SDL_DestroyWindow(screen_inst->window);

                sol_ptr_free((sol_ptr **) &screen_inst);
        }
}




extern sol_erno marek_screen_clear(const marek_shade *shade)
{
        auto sol_word alpha, red, green, blue;

SOL_TRY:
        sol_assert (shade, SOL_ERNO_PTR);
        sol_assert (screen_inst, SOL_ERNO_STATE);

        sol_try (marek_shade_alpha(shade, &alpha));
        sol_try (marek_shade_red(shade, &red));
        sol_try (marek_shade_green(shade, &green));
        sol_try (marek_shade_blue(shade, &blue));

        SDL_SetRenderDrawColor(screen_inst->renderer, alpha, red, green, blue);
        SDL_RenderClear(screen_inst->renderer);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno marek_screen_render(void)
{
SOL_TRY:
        sol_assert (screen_inst, SOL_ERNO_STATE);
        SDL_RenderPresent(screen_inst->renderer);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}

