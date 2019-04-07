#include "merak.h"




struct __merak_shade {
        sol_w8 alpha;
        sol_w8 red;
        sol_w8 green;
        sol_w8 blue;
};




extern sol_word merak_shade_spawn(merak_shade **shade,
                                  sol_word alpha,
                                  sol_word red,
                                  sol_word green,
                                  sol_word blue)
{
        auto merak_shade *ctx;

SOL_TRY:
        sol_try (sol_ptr_new((sol_ptr **) shade, sizeof (**shade)));
        ctx = *shade;

        sol_try (merak_shade_setalpha(ctx, alpha));
        sol_try (merak_shade_setred(ctx, red));
        sol_try (merak_shade_setgreen(ctx, green));
        sol_try (merak_shade_setblue(ctx, blue));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void merak_shade_kill(merak_shade **shade)
{
        sol_ptr_free((sol_ptr **) shade);
}




extern sol_erno merak_shade_alpha(const merak_shade *shade, sol_word *alpha)
{
SOL_TRY:
        sol_assert (shade && alpha, SOL_ERNO_PTR);

        *alpha = (sol_word) shade->alpha;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_shade_red(const merak_shade *shade, sol_word *red)
{
SOL_TRY:
        sol_assert (shade && red, SOL_ERNO_PTR);

        *red = (sol_word) shade->red;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_shade_green(const merak_shade *shade, sol_word *green)
{
SOL_TRY:
        sol_assert (shade && green, SOL_ERNO_PTR);

        *green = (sol_word) shade->green;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_shade_blue(const merak_shade *shade, sol_word *blue)
{
SOL_TRY:
        sol_assert (shade && blue, SOL_ERNO_PTR);

        *blue = (sol_word) shade->blue;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_shade_setalpha(merak_shade *shade, sol_word alpha)
{
SOL_TRY:
        sol_assert (shade, SOL_ERNO_PTR);

        shade->alpha = (sol_w8) alpha;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_shade_setred(merak_shade *shade, sol_word red)
{
SOL_TRY:
        sol_assert (shade, SOL_ERNO_PTR);

        shade->red = (sol_w8) red;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_shade_setgreen(merak_shade *shade, sol_word green)
{
SOL_TRY:
        sol_assert (shade, SOL_ERNO_PTR);

        shade->green = (sol_w8) green;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_shade_setblue(merak_shade *shade, sol_word blue)
{
SOL_TRY:
        sol_assert (shade, SOL_ERNO_PTR);

        shade->blue = (sol_w8) blue;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

