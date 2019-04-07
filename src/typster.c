#include <SDL2/SDL.h>
#include <stdio.h>
#include "marek/screen.h"


        /* status codes */
#define STATUS_OK 0
#define STATUS_ERROR 1


        /* handles the input for a frame */
void input(void)
{
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                        marek_screen_exit();
                        exit(STATUS_OK);
                        break;

                default:
                        break;
                }
        }
}


        /* updates the state of a frame */
void update(void)
{
        auto marek_shade *shade = NULL;

        (void) marek_shade_spawn(&shade, 96, 128, 128, 256);
        (void) marek_screen_clear(shade);
        marek_shade_kill(&shade);
}


        /* renders a frame */
void render(void)
{
        (void) marek_screen_render();
}


int main(int argc, char *argv[])
{
                /* cast arguments to void as we don't use them */
        (void) argc;
        (void) argv;

                /* initialise screen */
        if (marek_screen_init()) {
                goto error;
        }

                /* run game frame loop */
        while (1) {
                input();
                update();
                render();
        }

        return STATUS_OK;
error:
        return STATUS_ERROR;
}

