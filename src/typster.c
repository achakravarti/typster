#include <SDL2/SDL.h>
#include "merak/merak.h"
#include "typster.h"




static typster_enemy *enemy = SOL_PTR_NULL;




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
        auto merak_shade shade;

SOL_TRY:
        shade.red = 128;
        shade.green = 128;
        shade.blue = 255;
        shade.alpha = 96;
        sol_try (merak_screen_clear(&shade));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




        /* renders a frame */
sol_erno frame_render(void)
{
SOL_TRY:
        //sol_try (merak_screen_render());
        sol_assert (SOL_BOOL_TRUE, SOL_ERNO_STATE);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




int main(int argc, char *argv[])
{
        auto merak_area res;

SOL_TRY:
                /* cast arguments to void as we don't use them */
        (void) argc;
        (void) argv;

        sol_try (sol_log_open("typster.log"));
        res.width = 1280;
        res.height = 720;

        sol_try (merak_game_init(&frame_input, &frame_update, &frame_render));
        sol_try (merak_screen_init("Typster", &res, SOL_BOOL_TRUE));
        sol_try (merak_event_init());

        sol_try (typster_enemy_new(&enemy));
        sol_try (merak_game_register((merak_entity *) enemy));

        sol_try (merak_game_run());

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        typster_enemy_free(&enemy);

        merak_screen_exit();
        merak_event_exit();
        merak_game_exit();

        sol_log_close();
        return (int) sol_erno_get();
}

