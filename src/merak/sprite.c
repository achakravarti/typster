#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "merak.h"




struct __merak_sprite {
        merak_texture *tex;
        sol_u8 nrow;
        sol_u8 ncol;
};




extern sol_erno merak_sprite_new(merak_sprite **sprite,
                                 const char *fpath,
                                 sol_size nrow,
                                 sol_size ncol)
{
        auto merak_sprite *ctx;

SOL_TRY:
        sol_assert (nrow && ncol, SOL_ERNO_RANGE);
        sol_assert (nrow <= SOL_U8_MAX && ncol <= SOL_U8_MAX, SOL_ERNO_RANGE);

        sol_try (sol_ptr_new((sol_ptr **) sprite, sizeof (**sprite)));
        ctx = *sprite;

        ctx->nrow = nrow;
        ctx->ncol = ncol;

        ctx->tex = SOL_PTR_NULL;
        sol_try(merak_texture_new(&ctx->tex, fpath));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void merak_sprite_free(merak_sprite **sprite)
{
        if (sol_likely (sprite && *sprite))
                merak_texture_free(&(*sprite)->tex);

        sol_ptr_free((sol_ptr **) sprite);
}




extern sol_erno merak_sprite_area(const merak_sprite *sprite,
                                  merak_area *area)
{
SOL_TRY:
        sol_assert (sprite, SOL_ERNO_PTR);

        sol_try(merak_texture_area(sprite->tex, area));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}





extern sol_erno merak_sprite_nframe(const merak_sprite *sprite,
                                    sol_size *nframe)
{
SOL_TRY:
        sol_assert (sprite && nframe, SOL_ERNO_PTR);

        *nframe = sprite->nrow * sprite->ncol;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_sprite_draw(const merak_sprite *sprite,
                                  sol_index row,
                                  sol_index col,
                                  const merak_point *dst)
{
        auto merak_area area, clip;
        auto merak_point src;

SOL_TRY:
        sol_assert (sprite, SOL_ERNO_PTR);
        sol_assert (row <= sprite->nrow && col <= sprite->ncol, SOL_ERNO_RANGE);

        sol_try (merak_texture_area(sprite->tex, &area));
        clip.width = area.width / sprite->ncol;
        clip.height = area.height / sprite->nrow;

        src.x = clip.width * (col - 1);
        src.y = clip.height * (row - 1);
        sol_try (merak_texture_draw(sprite->tex, &src, &clip, dst));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

