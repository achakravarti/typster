#include <SDL2/SDL.h>
#include "merak.h"




extern sol_erno merak_event_init(void)
{
        return SOL_ERNO_NULL;
}




extern void merak_event_exit(void)
{
}




extern sol_erno merak_event_update(MERAK_EVENT_CODE *code)
{
        auto SDL_Event event;
        auto sol_int more;

        more = SDL_PollEvent(&event);

        if (sol_likely (more)) {
                switch (event.type) {
                case SDL_QUIT:
                        *code = MERAK_EVENT_CODE_QUIT;
                        break;

                default:
                        *code = MERAK_EVENT_CODE_IGNORED;
                        break;
                }
        }
        else {
                *code = MERAK_EVENT_CODE_NULL;
        }

        return SOL_ERNO_NULL;
}

