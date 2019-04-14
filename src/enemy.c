#include <SDL2/SDL.h>
#include "typster.h"




static sol_erno delegate_update(merak_entity *enemy)
{
        const sol_index row = 1;
        const sol_index col = ((SDL_GetTicks() / 100) % 4) + 1;

SOL_TRY:
        sol_try(merak_entity_setframe(enemy, row, col));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno typster_enemy_new(typster_enemy **enemy)
{
        auto merak_sprite *sprite = SOL_PTR_NULL;

SOL_TRY:
        sol_try (merak_sprite_new(&sprite, "res/typster.png", 1, 4));
        sol_try (merak_entity_new((merak_entity **) enemy,
                                  sprite,
                                  &delegate_update));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void typster_enemy_free(typster_enemy **enemy)
{
        merak_entity_free((merak_entity **) enemy);
}

