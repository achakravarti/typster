#include <SDL2/SDL.h>
#include "merak/merak.h"
#include "typster.h"




static typster_enemy *enemy = SOL_PTR_NULL;




        /* updates the state of a frame */
sol_erno frame_update(void)
{
        return SOL_ERNO_NULL;
}




        /* renders a frame */
sol_erno frame_render(void)
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

        sol_try (merak_game_init(&frame_update, &frame_render));
        sol_try (merak_screen_init("Typster", &res, SOL_BOOL_TRUE));
        sol_try (merak_event_init());
        sol_try (merak_arena_init());
        sol_try (merak_keyboard_init());

        sol_try (typster_enemy_new(&enemy));
        sol_try (merak_arena_push((merak_entity *) enemy));

        sol_try (merak_game_run());

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        typster_enemy_free(&enemy);

        merak_screen_exit();
        merak_event_exit();
        merak_keyboard_exit();
        merak_arena_exit();
        merak_game_exit();

        sol_log_close();
        return (int) sol_erno_get();
}

