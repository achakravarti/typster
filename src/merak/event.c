#include <SDL2/SDL.h>
#include "merak.h"




#define EVENT_COUNT 3




static sol_tls merak_game_delegate *delegate_list[EVENT_COUNT];




static sol_tls SOL_BOOL delegate_init = SOL_BOOL_FALSE;




static sol_erno delegate_run(const MERAK_EVENT_CODE event)
{
        if (delegate_list[event])
                return delegate_list[event]();

        return SOL_ERNO_NULL;
}




extern sol_erno merak_event_init(void)
{
        register sol_index i;

        for (i = 0; i < EVENT_COUNT; i++)
                delegate_list[i] = SOL_PTR_NULL;

        delegate_init = SOL_BOOL_TRUE;
        return SOL_ERNO_NULL;
}




extern void merak_event_exit(void)
{
        register sol_index i;

        for (i = 0; i < EVENT_COUNT; i++)
                delegate_list[i] = SOL_PTR_NULL;
}




extern sol_erno merak_event_register(const MERAK_EVENT_CODE event,
                                     merak_game_delegate *handler)
{
SOL_TRY:
        sol_assert (delegate_init, SOL_ERNO_STATE);
        sol_assert (handler, SOL_ERNO_PTR);

        delegate_list[event] = handler;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_event_update(void)
{
        auto SDL_Event event;

SOL_TRY:
        sol_assert (delegate_init, SOL_ERNO_STATE);

        while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                        sol_try (delegate_run(MERAK_EVENT_CODE_QUIT));
                        merak_screen_exit();
                        merak_keyboard_exit();
                        merak_event_exit();
                        merak_game_exit();
                        break;

                case SDL_KEYUP:
                        sol_try (merak_keyboard_update());
                        sol_try (delegate_run(MERAK_EVENT_CODE_KEYUP));
                        break;

                case SDL_KEYDOWN:
                        sol_try (merak_keyboard_update());
                        sol_try (delegate_run(MERAK_EVENT_CODE_KEYDOWN));
                        break;

                default:
                        break;
                }
        }

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

