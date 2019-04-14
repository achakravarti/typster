#include "merak.h"

struct __merak_entity {
        merak_sprite *sprite;
        merak_entity_delegate *update;
        merak_entity_delegate *draw;
        merak_point pos;
};




static sol_erno draw_default(merak_entity *entity)
{
SOL_TRY:
        sol_assert (entity, SOL_ERNO_PTR);

        sol_try (merak_sprite_draw(entity->sprite, 1, 1, &entity->pos));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_entity_new(merak_entity **entity,
                                 merak_sprite *sprite,
                                 merak_entity_delegate *update)
{
SOL_TRY:
        sol_try (merak_entity_new2(entity, sprite, update, &draw_default));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_entity_new2(merak_entity **entity,
                                  merak_sprite *sprite,
                                  merak_entity_delegate *update,
                                  merak_entity_delegate *draw)
{
        auto merak_entity *ctx;

SOL_TRY:
        sol_assert (sprite && update && draw, SOL_ERNO_PTR);

        sol_try (merak_entity_new(entity, sprite, update));
        (*entity)->draw = draw_default;

        sol_try (sol_ptr_new((sol_ptr **) entity, sizeof (**entity)));
        ctx = *entity;

        ctx->sprite = sprite;
        ctx->update = update;
        ctx->draw = draw;
        ctx->pos.x = ctx->pos.y = 0;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void merak_entity_free(merak_entity **entity)
{
        if (sol_likely (entity && *entity))
                merak_sprite_free (&(*entity)->sprite);

        sol_ptr_free((sol_ptr **) entity);
}




extern sol_erno merak_entity_pos(const merak_entity *entity, merak_point *pos)
{
SOL_TRY:
        sol_assert (entity && pos, SOL_ERNO_PTR);

        *pos = entity->pos;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_entity_setpos(merak_entity *entity,
                                    const merak_point *pos)
{
SOL_TRY:
        sol_assert (entity && pos, SOL_ERNO_PTR);

        entity->pos = *pos;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_entity_sprite(const merak_entity *entity,
                                    merak_sprite *sprite)
{
SOL_TRY:
        sol_assert (entity && !sprite, SOL_ERNO_PTR);

        sprite = entity->sprite;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_entity_update(merak_entity *entity)
{
SOL_TRY:
        sol_assert (entity, SOL_ERNO_PTR);

        sol_try (entity->update(entity));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_entity_draw(merak_entity *entity)
{
SOL_TRY:
        sol_assert (entity, SOL_ERNO_PTR);

        sol_try (entity->draw(entity));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

