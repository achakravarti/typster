#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "marek.h"




struct screen {
        SDL_Renderer *renderer;
        SDL_Window *window;
};




struct screen *screen_instance(void)
{
        static struct screen *instance = NULL;

        if (!instance) {
                if ((instance = malloc(sizeof (*instance)))) {
                        instance->renderer = NULL;
                        instance->window = NULL;
                }

        }

        return instance;
}




extern sol_erno marek_screen_init(void)
{
        const int wflag = 0;
        const int rflag = SDL_RENDERER_ACCELERATED;
        const int width = 1280;
        const int height = 720;
        auto struct screen *instance;

SOL_TRY:
        sol_assert (SDL_Init(SDL_INIT_VIDEO) >= 0, SOL_ERNO_STATE);

        sol_assert ((instance = screen_instance()), SOL_ERNO_STATE);
        instance->window = SDL_CreateWindow("Typster",
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            width,
                                            height,
                                            wflag);
        sol_assert (instance->window, SOL_ERNO_STATE);

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        instance->renderer = SDL_CreateRenderer(instance->window, -1, rflag);
        sol_assert (instance->renderer, SOL_ERNO_STATE);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}




extern void marek_screen_exit(void)
{
        auto struct screen *instance;

        if ((instance = screen_instance())) {
                SDL_DestroyRenderer(instance->renderer);
                SDL_DestroyWindow(instance->window);
                SDL_Quit();

                sol_ptr_free((sol_ptr **) &instance);
        }
}




extern sol_erno marek_screen_clear(const marek_shade *shade)
{
        auto struct screen *instance;
        auto sol_word alpha, red, green, blue;

SOL_TRY:
        sol_assert (shade, SOL_ERNO_PTR);

        sol_try (marek_shade_alpha(shade, &alpha));
        sol_try (marek_shade_red(shade, &red));
        sol_try (marek_shade_green(shade, &green));
        sol_try (marek_shade_blue(shade, &blue));

        sol_assert ((instance = screen_instance()), SOL_ERNO_STATE);
        SDL_SetRenderDrawColor(instance->renderer, alpha, red, green, blue);
        SDL_RenderClear(instance->renderer);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno marek_screen_render(void)
{
        auto struct screen *instance;

SOL_TRY:
        sol_assert ((instance = screen_instance()), SOL_ERNO_STATE);
        SDL_RenderPresent(instance->renderer);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}

