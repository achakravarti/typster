#include <SDL2/SDL.h>
#include "merak.h"




struct __merak_texture {
        SDL_Texture *tex;
        merak_area *area;
};




extern sol_erno merak_texture_new(merak_texture **tex,
                                  const char *fpath,
                                  MERAK_TEXTURE_MIME ftype)
{
        auto merak_texture *ctx = SOL_PTR_NULL;
        auto SDL_Surface *surf = SOL_PTR_NULL;
        auto SDL_Renderer *brush = SOL_PTR_NULL;
        auto int width, height;

SOL_TRY:
        sol_assert (fpath && *fpath, SOL_ERNO_STR);

        sol_try (sol_ptr_new((sol_ptr **) tex, sizeof (**tex)));
        ctx = *tex;
        ctx->tex = SOL_PTR_NULL;
        ctx->area = SOL_PTR_NULL;

        if (ftype == MERAK_TEXTURE_MIME_BMP) {
                sol_try (merak_screen_brush((sol_ptr *) brush));
                surf = SDL_LoadBMP(fpath);
                ctx->tex = SDL_CreateTextureFromSurface(brush, surf);
        }

        SDL_QueryTexture(ctx->tex, SOL_PTR_NULL, SOL_PTR_NULL, &width, &height);
        sol_try (merak_area_new(&ctx->area, width, height));

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

        if (sol_likely (tex && *tex)) {
                ctx = *tex;

                if (sol_likely (ctx)) {
                        SDL_DestroyTexture(ctx->tex);
                }

                merak_area_free(&ctx->area);
        }

        sol_ptr_free((sol_ptr **) tex);
}




extern sol_erno merak_texture_area(const merak_texture *tex,
                                   merak_area **area)
{
SOL_TRY:
        sol_assert (tex && area, SOL_ERNO_PTR);

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
        auto SDL_Rect src, dst;

SOL_TRY:
        sol_assert (tex, SOL_ERNO_PTR);

        src.x = src.y = 0;
        sol_try (merak_area_width(tex->area, (sol_uint *) &src.w));
        sol_try (merak_area_height(tex->area, (sol_uint *) &src.h));

        sol_try (merak_point_x(loc, (sol_uint *) &dst.x));
        sol_try (merak_point_y(loc, (sol_uint *) &dst.y));
        dst.w = src.w;
        dst.h = src.h;

        sol_try (merak_screen_brush((sol_ptr *) brush));
        SDL_RenderCopy(brush, tex->tex, &src, &dst);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());

SOL_FINALLY:
        return sol_erno_get();
}

