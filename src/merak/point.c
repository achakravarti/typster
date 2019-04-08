#include "merak.h"




struct __merak_point {
        sol_u16 x;
        sol_u16 y;
};




extern sol_erno merak_point_spawn(merak_point **point,
                                 sol_uint x,
                                 sol_uint y)
{
        auto merak_point *ctx;

SOL_TRY:
        sol_assert (x <= SOL_U16_MAX && y <= SOL_U16_MAX,
                    SOL_ERNO_RANGE);

        sol_try (sol_ptr_new((sol_ptr **) point, sizeof (**point)));
        ctx = *point;

        ctx->x = x;
        ctx->y = y;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void merak_point_kill(merak_point **point)
{
        sol_ptr_free((sol_ptr **) point);
}




extern sol_erno merak_point_x(const merak_point *point, sol_uint *x)
{
SOL_TRY:
        sol_assert (point && x, SOL_ERNO_PTR);

        *x = point->x;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_point_y(const merak_point *point, sol_uint *y)
{
SOL_TRY:
        sol_assert (point && y, SOL_ERNO_PTR);

        *y = point->y;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_point_setx(merak_point *point, sol_uint x)
{
SOL_TRY:
        sol_assert (point, SOL_ERNO_PTR);
        sol_assert (x <= SOL_U16_MAX, SOL_ERNO_RANGE);

        point->x = x;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_point_sety(merak_point *point, sol_uint y)
{
SOL_TRY:
        sol_assert (point, SOL_ERNO_PTR);
        sol_assert (y <= SOL_U16_MAX, SOL_ERNO_RANGE);

        point->y = y;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




