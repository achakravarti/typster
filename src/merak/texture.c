#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "merak.h"




struct __merak_texture {
        SDL_Texture *tex;
        SDL_Rect rect;
};




extern sol_erno merak_texture_new(merak_texture **tex, const char *fpath)
{
        auto merak_texture *ctx = SOL_PTR_NULL;
        auto SDL_Renderer *brush = SOL_PTR_NULL;

SOL_TRY:
        sol_assert (fpath && *fpath, SOL_ERNO_STR);

        sol_try (sol_ptr_new((sol_ptr **) tex, sizeof (**tex)));
        ctx = *tex;

        sol_try (merak_screen_brush((sol_ptr **) &brush));
        sol_assert (ctx->tex = IMG_LoadTexture(brush, fpath), SOL_ERNO_STATE);

        ctx->rect.x = ctx->rect.y = 0;
        SDL_QueryTexture(ctx->tex,
                         SOL_PTR_NULL,
                         SOL_PTR_NULL,
                         &ctx->rect.w,
                         &ctx->rect.h);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());
        sol_log_error(IMG_GetError());

SOL_FINALLY:
        return sol_erno_get();
}




extern void merak_texture_free(merak_texture **tex)
{
        auto merak_texture *ctx;

        if (sol_likely (tex && (ctx = *tex))) {
                if (sol_likely (ctx->tex)) {
                        SDL_DestroyTexture(ctx->tex);
                }
        }

        sol_ptr_free((sol_ptr **) tex);
}




extern sol_erno merak_texture_area(const merak_texture *tex,
                                   merak_area *area)
{
SOL_TRY:
        sol_assert (tex && area, SOL_ERNO_PTR);

        area->width = tex->rect.w;
        area->height = tex->rect.h;

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_texture_render(const merak_texture *tex,
                                     const merak_point *dst)
{
        auto SDL_Renderer *brush = SOL_PTR_NULL;
        auto SDL_Rect rdst;

SOL_TRY:
        sol_assert (tex && dst, SOL_ERNO_PTR);

        rdst.x = dst->x;
        rdst.y = dst->y;
        rdst.w = tex->rect.w;
        rdst.h = tex->rect.h;

        sol_try (merak_screen_brush((sol_ptr **) &brush));
        SDL_RenderCopy(brush, tex->tex, SOL_PTR_NULL, &rdst);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_texture_draw(const merak_texture *tex,
                                   const merak_point *src,
                                   const merak_area *clip,
                                   const merak_point *dst)
{
        auto SDL_Renderer *brush = SOL_PTR_NULL;
        auto SDL_Rect rsrc, rdst;

SOL_TRY:
        sol_assert (tex && src && dst && clip, SOL_ERNO_PTR);
        sol_assert (src->x <= tex->rect.w
                    && src->y <= tex->rect.h
                    && clip->width <= tex->rect.w
                    && clip->height <= tex->rect.h,
                    SOL_ERNO_RANGE);

        rsrc.x = src->x;
        rsrc.y = src->y;
        rsrc.w = clip->width;
        rsrc.h = clip->height;

        rdst.x = dst->x;
        rdst.y = dst->y;
        rdst.w = rsrc.w;
        rdst.h = rsrc.h;

        sol_try (merak_screen_brush((sol_ptr **) &brush));
        SDL_RenderCopy(brush, tex->tex, &rsrc, &rdst);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}

