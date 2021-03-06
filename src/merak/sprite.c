#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "merak.h"




struct __merak_sprite {
        merak_texture *tex;
        sol_u8 nrow;
        sol_u8 ncol;
        sol_u8 row;
        sol_u8 col;
        sol_size nref;
};




extern sol_erno merak_sprite_new(merak_sprite **sprite,
                                 const char *fpath,
                                 sol_size nrow,
                                 sol_size ncol)
{
        auto merak_sprite *ctx;

SOL_TRY:
        sol_assert (nrow && ncol, SOL_ERNO_RANGE);
        sol_assert (nrow >= 1
                    && nrow <= SOL_U8_MAX
                    && ncol >= 1
                    && ncol <= SOL_U8_MAX,
                    SOL_ERNO_RANGE);

        sol_try (sol_ptr_new((sol_ptr **) sprite, sizeof (**sprite)));
        ctx = *sprite;
        ctx->nref = (sol_size) 1;

        ctx->nrow = nrow;
        ctx->ncol = ncol;
        ctx->row = ctx->col = 1;

        ctx->tex = SOL_PTR_NULL;
        sol_try(merak_texture_new(&ctx->tex, fpath));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_sprite_copy(merak_sprite **lhs, merak_sprite *rhs)
{
SOL_TRY:
        sol_assert (lhs && rhs, SOL_ERNO_PTR);
        sol_assert (!*lhs, SOL_ERNO_STATE);

        rhs->nref++;
        *lhs = rhs;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void merak_sprite_free(merak_sprite **sprite)
{
        auto merak_sprite *hnd;

        if (sol_likely (sprite && (hnd = *sprite))) {
                if (!(--hnd->nref)) {
                        merak_texture_free(&hnd->tex);
                        sol_ptr_free((sol_ptr **) sprite);
                }
        }
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




extern sol_erno merak_sprite_frame(const merak_sprite *sprite,
                                   sol_index *row,
                                   sol_index *col)
{
SOL_TRY:
        sol_assert (sprite && row && col, SOL_ERNO_PTR);

        *row = sprite->row;
        *col = sprite->col;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_sprite_setframe(merak_sprite *sprite,
                                      sol_index row,
                                      sol_index col)
{
SOL_TRY:
        sol_assert (sprite, SOL_ERNO_PTR);
        sol_assert (row >= 1
                    && row <= sprite->nrow
                    && col >= 1
                    && col <= sprite->ncol,
                    SOL_ERNO_RANGE);

        sprite->row = row;
        sprite->col = col;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_sprite_draw(const merak_sprite *sprite,
                                  const merak_point *pos)
{
        auto merak_area area, clip;
        auto merak_point src;

SOL_TRY:
        sol_assert (sprite, SOL_ERNO_PTR);

        sol_try (merak_texture_area(sprite->tex, &area));
        clip.width = area.width / sprite->ncol;
        clip.height = area.height / sprite->nrow;

        src.x = clip.width * (sprite->col - 1);
        src.y = clip.height * (sprite->row - 1);
        sol_try (merak_texture_draw(sprite->tex, &src, &clip, pos));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

