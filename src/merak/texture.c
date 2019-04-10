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
        auto SDL_Surface *surf = SOL_PTR_NULL;
        auto SDL_Renderer *brush = SOL_PTR_NULL;

SOL_TRY:
        sol_assert (fpath && *fpath, SOL_ERNO_STR);

        sol_try (sol_ptr_new((sol_ptr **) tex, sizeof (**tex)));
        ctx = *tex;

        surf = IMG_Load(fpath);
        sol_try (merak_screen_brush((sol_ptr **) &brush));
        ctx->tex = SDL_CreateTextureFromSurface(brush, surf);
        sol_assert (ctx->tex, SOL_ERNO_STATE);

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

SOL_FINALLY:
        if (sol_likely (surf)) {
                SDL_FreeSurface(surf);
        }

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
                                   merak_area **area)
{
SOL_TRY:
        sol_assert (tex && area, SOL_ERNO_PTR);

        sol_try (merak_area_new(area, tex->rect.w, tex->rect.h));

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_texture_render(const merak_texture *tex,
                                     const merak_point *loc)
{
        auto SDL_Renderer *brush = SOL_PTR_NULL;
        auto SDL_Rect dst;

SOL_TRY:
        sol_assert (tex, SOL_ERNO_PTR);

        sol_try (merak_point_x(loc, (sol_uint *) &dst.x));
        sol_try (merak_point_y(loc, (sol_uint *) &dst.y));
        dst.w = tex->rect.w;
        dst.h = tex->rect.h;

        sol_try (merak_screen_brush((sol_ptr **) &brush));
        SDL_RenderCopy(brush, tex->tex, SOL_PTR_NULL, &dst);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}

