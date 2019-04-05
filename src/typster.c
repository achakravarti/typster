#include <SDL2/SDL.h>
#include <stdio.h>


        /* status codes */
#define STATUS_OK 0
#define STATUS_ERROR 1


        /* video device */
typedef struct __typster_video {
        SDL_Renderer *screen;
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

                /* create screen */
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        video->screen = SDL_CreateRenderer(video->window, -1, rflag);

                /* handle screen creation exception */
        if (!video->screen) {
                printf("Failed to create screen: %s\n", SDL_GetError());
                return STATUS_ERROR;
        }

        return STATUS_OK;
}


        /* clears the screen */
void typster_video_clear(typster_video *video)
{
        SDL_SetRenderDrawColor(video->screen, 96, 128, 255, 255);
        SDL_RenderClear(video->screen);
}


        /* renders the screen */
void typster_video_render(typster_video *video)
{
        SDL_RenderPresent(video->screen);
}


        /* handles the input for a frame */
void input(void)
{
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                        exit(STATUS_OK);
                        break;
                default:
                        break;
                }
}


        /* updates the state of a frame */
void update(typster_video *video)
{
        typster_video_clear(video);
}


        /* renders a frame */
void render(typster_video *video)
{
        typster_video_render(video);
}


int main(int argc, char *argv[])
{
        auto typster_video __video, *video = &__video;

                /* initialise video device */
        if (typster_video_ctor(video)) {
                printf("Failed to initialise video device\n");
                return STATUS_ERROR;
        }

                /* run game frame loop */
        while (1) {
                input();
                update(video);
                render(video);
        }

        return STATUS_OK;
}

