#include <SDL2/SDL.h>
#include <stdio.h>


        /* status codes */
#define STATUS_OK 0
#define STATUS_ERROR 1


        /* video device */
typedef struct __typster_video {
        SDL_Renderer *renderer;
        SDL_Window *window;
} typster_video;


        /* constructs a video device instance */
int typster_video_ctor(typster_video *video)
{
        const int wflag = 0;
        const int rflag = SDL_RENDERER_ACCELERATED;
        const int width = 1280;
        const int height = 720;

                /* initialise SDL */
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                printf("Couldn't initialise SDL: %s\n", SDL_GetError());
                return STATUS_ERROR;
        }

                /* create window */
        video->window = SDL_CreateWindow(
                "Typster",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                height,
                width,
                wflag
        );

                /* handle window creation exception */
        if (!video->window) {
                printf("Failed to create window: %s\n", SDL_GetError());
                return STATUS_ERROR;
        }

                /* create renderer */
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        video->renderer = SDL_CreateRenderer(video->window, -1, rflag);

                /* handle renderer creation exception */
        if (!video->renderer) {
                printf("Failed to create renderer: %s\n", SDL_GetError());
                return STATUS_ERROR;
        }

        return STATUS_OK;
}


        /* handles the input for a frame */
void input(void)
{
}


        /* updates the state of a frame */
void update(void)
{
}


        /* renders a frame */
void render(void)
{
}


int main(int argc, char *argv[])
{
        auto typster_video video;

                /* initialise video device */
        if (typster_video_ctor(&video)) {
                printf("Failed to initialise video device\n");
                return STATUS_ERROR;
        }

                /* run game frame loop */
        while (1) {
                input();
                update();
                render();
        }

        return STATUS_OK;
}

