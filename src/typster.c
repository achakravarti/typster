#include "merak/merak.h"




        /* handles the input for a frame */
sol_erno frame_input(void)
{
        auto MERAK_EVENT_CODE code;

SOL_TRY:
        sol_try (merak_event_poll(&code));

        while (code) {
                switch (code) {
                case MERAK_EVENT_CODE_QUIT:
                        merak_screen_exit();
                        merak_event_exit();
                        merak_game_exit();
                        break;

                default:
                        break;
                }

                sol_try (merak_event_poll(&code));
        }

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();

}




        /* updates the state of a frame */
sol_erno frame_update(void)
{
        auto merak_shade *shade = SOL_PTR_NULL;

SOL_TRY:
        sol_try (merak_shade_new(&shade, 96, 128, 128, 256));
        sol_try (merak_screen_clear(shade));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        merak_shade_free(&shade);
        return sol_erno_get();
}




        /* renders a frame */
sol_erno frame_render(void)
{
SOL_TRY:
        sol_try (merak_screen_render());

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




int main(int argc, char *argv[])
{
        auto merak_area *res = SOL_PTR_NULL;

SOL_TRY:
                /* cast arguments to void as we don't use them */
        (void) argc;
        (void) argv;

        sol_try (merak_area_new(&res, 1280, 720));

        sol_try (merak_game_init(&frame_input, &frame_update, &frame_render));
        sol_try (merak_screen_init("Typster", res, SOL_BOOL_TRUE));
        sol_try (merak_event_init());

        sol_try (merak_game_run());

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        merak_area_free(&res);

        merak_screen_exit();
        merak_event_exit();
        merak_game_exit();

        return (int) sol_erno_get();
}

