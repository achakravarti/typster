#include <SDL2/SDL.h>
#include "marek.h"




extern sol_erno marek_event_init(void)
{
        return SOL_ERNO_NULL;
}




extern void marek_event_exit(void)
{
}




extern sol_erno marek_event_poll(MAREK_EVENT_CODE *code)
{
        auto SDL_Event event;
        auto sol_int more;

        more = SDL_PollEvent(&event);

        if (sol_likely (more)) {
                switch (event.type) {
                case SDL_QUIT:
                        *code = MAREK_EVENT_CODE_QUIT;
                        break;

                default:
                        *code = MAREK_EVENT_CODE_IGNORED;
                        break;
                }
        }
        else {
                *code = MAREK_EVENT_CODE_NULL;
        }

        return SOL_ERNO_NULL;
}

