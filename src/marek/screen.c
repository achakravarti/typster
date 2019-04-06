#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "screen.h"




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




int marek_screen_init(void)
{
        const int wflag = 0;
        const int rflag = SDL_RENDERER_ACCELERATED;
        const int width = 1280;
        const int height = 720;
        auto struct screen *instance;

        if (!(instance = screen_instance())) {
                goto error;
        }

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                goto error;
        }

        instance->window = SDL_CreateWindow(
                "Typster",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                width,
                height,
                wflag
        );

        if (!instance->window) {
                goto error;
        }

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        instance->renderer = SDL_CreateRenderer(instance->window, -1, rflag);

        if (!instance->renderer) {
                goto error;
        }

        return 0;
error:
        printf("SDL says: %s\n", SDL_GetError());
        return 1;
}




void marek_screen_exit(void)
{
        auto struct screen *instance;

        if ((instance = screen_instance())) {
                SDL_DestroyRenderer(instance->renderer);
                SDL_DestroyWindow(instance->window);
                SDL_Quit();
        }
}




int marek_screen_clear(void)
{
        auto struct screen *instance;

        if (!(instance = screen_instance())) {
                goto error;
        }

        SDL_SetRenderDrawColor(instance->renderer, 96, 128, 255, 255);
        SDL_RenderClear(instance->renderer);

        return 0;
error:
        printf("SDL says: %s\n", SDL_GetError());
        return 1;
}




int marek_screen_render(void)
{
        auto struct screen *instance;

        if (!(instance = screen_instance())) {
                goto error;
        }

        SDL_RenderPresent(instance->renderer);

        return 0;
error:
        printf("SDL says: %s\n", SDL_GetError());
        return 1;
}

