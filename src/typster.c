#include <SDL2/SDL.h>


        /* video device */
typedef struct __typster_video {
        SDL_Renderer *renderer;
        SDL_Window *window;
} typster_video;


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
                /* run game loop */
        while (1) {
                input();
                update();
                render();
        }

        return 0;
}

