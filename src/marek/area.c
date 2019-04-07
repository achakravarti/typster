#include "marek.h"




struct __marek_area {
        sol_u16 width;
        sol_u16 height;
};




extern sol_erno marek_area_spawn(marek_area **area,
                                 sol_uint width,
                                 sol_uint height)
{
        auto marek_area *ctx;

SOL_TRY:
        sol_assert (width <= SOL_U16_MAX && height <= SOL_U16_MAX,
                    SOL_ERNO_RANGE);

        sol_try (sol_ptr_new((sol_ptr **) area, sizeof (**area)));
        ctx = *area;

        ctx->width = width;
        ctx->height = height;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void marek_area_kill(marek_area **area)
{
        sol_ptr_free((sol_ptr **) area);
}




extern sol_erno marek_area_width(const marek_area *area, sol_uint *width)
{
SOL_TRY:
        sol_assert (area && width, SOL_ERNO_PTR);

        *width = area->width;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno marek_area_height(const marek_area *area, sol_uint *height)
{
SOL_TRY:
        sol_assert (area && height, SOL_ERNO_PTR);

        *height = area->height;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno marek_area_setwidth(marek_area *area, sol_uint width)
{
SOL_TRY:
        sol_assert (area, SOL_ERNO_PTR);
        sol_assert (width <= SOL_U16_MAX, SOL_ERNO_RANGE);

        area->width = width;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno marek_area_setheight(marek_area *area, sol_uint height)
{
SOL_TRY:
        sol_assert (area, SOL_ERNO_PTR);
        sol_assert (height <= SOL_U16_MAX, SOL_ERNO_RANGE);

        area->height = height;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




