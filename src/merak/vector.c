#include "merak.h"
#include <math.h>




struct __merak_vector {
        sol_f32 x;
        sol_f32 y;
};




extern sol_erno merak_vector_new(merak_vector **vec)
{
        const sol_float def = (sol_float) 0.0;

SOL_TRY:
        sol_try (merak_vector_new2(vec, def, def));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_vector_new2(merak_vector **vec,
                                  const sol_float x,
                                  const sol_float y)
{
        auto merak_vector *hnd;

SOL_TRY:
        sol_assert (vec, SOL_ERNO_PTR);

        sol_try (sol_ptr_new((sol_ptr **) vec, sizeof (**vec)));
        hnd = *vec;

        hnd->x = (sol_f32) x;
        hnd->y = (sol_f32) y;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_vector_copy(merak_vector **lhs, const merak_vector *rhs)
{
SOL_TRY:
        sol_assert (rhs, SOL_ERNO_PTR);

        sol_try (merak_vector_new2(lhs,
                                   (sol_float) rhs->x,
                                   (sol_float) rhs->y));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void merak_vector_free(merak_vector **vec)
{
        sol_ptr_free((sol_ptr **) vec);
}




extern sol_erno merak_vector_x(const merak_vector *vec, sol_float *x)
{
SOL_TRY:
        sol_assert (vec && x, SOL_ERNO_PTR);

        *x = (sol_float) vec->x;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_vector_y(const merak_vector *vec, sol_float *y)
{
SOL_TRY:
        sol_assert (vec && y, SOL_ERNO_PTR);

        *y = (sol_float) vec->y;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_vector_len(const merak_vector *vec, sol_float *len)
{
SOL_TRY:
        sol_assert (vec, SOL_ERNO_PTR);

        *len = (sol_float) sqrt((double) (vec->x * vec->x)
                                + (double) (vec->y * vec->y));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_vector_setx(merak_vector *vec, const sol_float x)
{
SOL_TRY:
        sol_assert (vec, SOL_ERNO_PTR);

        vec->x = (sol_f32) x;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_vector_sety(merak_vector *vec, const sol_float y)
{
SOL_TRY:
        sol_assert (vec, SOL_ERNO_PTR);

        vec->y = (sol_f32) y;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_vector_add(merak_vector *lhs, const merak_vector *rhs)
{
SOL_TRY:
        sol_assert (rhs, SOL_ERNO_PTR);

        sol_try (merak_vector_add2(lhs,
                                   (sol_float) rhs->x,
                                   (sol_float) rhs->y));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_vector_add2(merak_vector *vec,
                                  const sol_float x,
                                  const sol_float y)
{
SOL_TRY:
        sol_assert (vec, SOL_ERNO_PTR);

        vec->x += (sol_f32) x;
        vec->y += (sol_f32) y;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_vector_sub(merak_vector *lhs, const merak_vector *rhs)
{
SOL_TRY:
        sol_assert (rhs, SOL_ERNO_PTR);

        sol_try (merak_vector_sub2(lhs,
                                   (sol_float) rhs->x,
                                   (sol_float) rhs->y));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_vector_sub2(merak_vector *vec,
                                  const sol_float x,
                                  const sol_float y)
{
SOL_TRY:
        sol_assert (vec, SOL_ERNO_PTR);

        vec->x -= (sol_f32) x;
        vec->y -= (sol_f32) y;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_vector_mul(merak_vector *vec, const sol_float scalar)
{
SOL_TRY:
        sol_assert (vec, SOL_ERNO_PTR);

        vec->x *= (sol_f32) scalar;
        vec->y *= (sol_f32) scalar;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




static inline SOL_BOOL float_nonzero(sol_float f)
{
        const double zero = 0.0;
        const double delta = 0.000001;

        return fabs((double) f - zero) < delta
               ? SOL_BOOL_TRUE
               : SOL_BOOL_FALSE;
}




extern sol_erno merak_vector_div(merak_vector *vec, const sol_float scalar)
{
SOL_TRY:
        sol_assert (vec, SOL_ERNO_PTR);
        sol_assert (float_nonzero(scalar), SOL_ERNO_RANGE);

        vec->x /= (sol_f32) scalar;
        vec->y /= (sol_f32) scalar;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_vector_norm(merak_vector *vec)
{
        auto sol_float len;

SOL_TRY:
        sol_try (merak_vector_len(vec, &len));

        if (sol_likely (float_nonzero(len)))
                sol_try (merak_vector_mul(vec, (1.0 / len)));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

