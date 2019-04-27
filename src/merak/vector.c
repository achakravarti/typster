/******************************************************************************
 *                               MERAK LIBRARY
 *
 * File: merak/src/vector.c
 *
 * Description:
 *      This file is part of the internal implementation of the Merak Library.
 *      It implements the vector interface.
 *
 * Authors:
 *      Abhishek Chakravarti <abhishek@taranjali.org>
 *
 * Copyright:
 *      (c) 2019 Abhishek Chakravarti
 *      <abhishek@taranjali.org>
 *
 * License:
 *      Released under the GNU General Public License version 3 (GPLv3)
 *      <http://opensource.org/licenses/GPL-3.0>. See the accompanying LICENSE
 *      file for complete licensing details.
 *
 *      BY CONTINUING TO USE AND/OR DISTRIBUTE THIS FILE, YOU ACKNOWLEDGE THAT
 *      YOU HAVE UNDERSTOOD THESE LICENSE TERMS AND ACCEPT THEM.
 ******************************************************************************/




        /* include required header files */
#include "merak.h"
#include <math.h>




        /* define the __merak_vector struct that was forward-declared in the
         * merak/merak.h header file; this struct contains the following fields:
         *   - x: the x coordinate
         *   - y: the y coordinate */
struct __merak_vector {
        sol_f32 x;
        sol_f32 y;
};




        /* define the epsilon value used for comparing floating-point values */
#define FLOAT_EPSILON (0.000001f)




        /* implement the merak_vector_new() interface function; we defer the
         * precondition check for @vec to merak_vector_new2() */
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




        /* implement the merak_vector_new2() interface function; we defer the
         * precondition check for @vec to sol_ptr_new() */
extern sol_erno merak_vector_new2(merak_vector **vec,
                                  const sol_float x,
                                  const sol_float y)
{
        auto merak_vector *hnd;

SOL_TRY:
        sol_try (sol_ptr_new((sol_ptr **) vec, sizeof (**vec)));
        hnd = *vec;

        hnd->x = (sol_f32) x;
        hnd->y = (sol_f32) y;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




        /* implement the merak_vector_copy() interface function; we defer the
         * precondition check for @lhs to merak_vector_new2() */
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




        /* implement the merak_vector_free() interface function */
extern void merak_vector_free(merak_vector **vec)
{
        sol_ptr_free((sol_ptr **) vec);
}




        /* implement the merak_vector_x() interface function */
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




        /* implement the merak_vector_y() interface function */
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




        /* implement the merak_vector_len() interface function; the length of a
         * vector is calculated by deriving the square root of the sum of
         * squares of its x and y components: (x^2 + y^2)^1/2 */
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




        /* implement the merak_vector_setx() interface function */
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




        /* implement the merak_vector_sety() interface function */
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




        /* implement the merak_vector_norm() interface function; we get the
         * normal form of a vector by multiplying it with the inverse of its
         * length; we need to ensure that the length of @vec is non-zero */
extern sol_erno merak_vector_norm(merak_vector *vec)
{
        auto sol_float len;

SOL_TRY:
        sol_try (merak_vector_len(vec, &len));

        if (sol_likely (!sol_float_eq(len, (sol_float) 0.0, FLOAT_EPSILON)))
                sol_try (merak_vector_mul(vec, (1.0 / len)));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




        /* implement the merak_vector_lt() interface function; a vector is
         * considered to be less than another if the length of the former is
         * less than that of the latter; we use the float_lt() utility function
         * defined above to perform a safe comparison */
extern sol_erno merak_vector_lt(const merak_vector *lhs,
                                const merak_vector *rhs,
                                SOL_BOOL *lt)
{
        auto sol_float llen, rlen;

SOL_TRY:
        sol_assert (lt, SOL_ERNO_PTR);

        sol_try (merak_vector_len(lhs, &llen));
        sol_try (merak_vector_len(rhs, &rlen));
        *lt = sol_float_lt(llen, rlen, FLOAT_EPSILON);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




        /* implement the merak_vector_eq() interface function; a vector is
         * considered to be equal to another if the length of the former is
         * equal to that of the latter; we use the float_eq() utility function
         * defined above to perform a safe comparison */
extern sol_erno merak_vector_eq(const merak_vector *lhs,
                                const merak_vector *rhs,
                                SOL_BOOL *eq)
{
        auto sol_float llen, rlen;

SOL_TRY:
        sol_assert (eq, SOL_ERNO_PTR);

        sol_try (merak_vector_len(lhs, &llen));
        sol_try (merak_vector_len(rhs, &rlen));
        *eq = sol_float_eq(llen, rlen, FLOAT_EPSILON);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




        /* implement the merak_vector_gt() interface function; a vector is
         * considered to be greater than another if the length of the former is
         * greater than that of the latter; we use the float_gt() utility
         * function defined above to perform a safe comparison */
extern sol_erno merak_vector_gt(const merak_vector *lhs,
                                const merak_vector *rhs,
                                SOL_BOOL *gt)
{
        auto sol_float llen, rlen;

SOL_TRY:
        sol_assert (gt, SOL_ERNO_PTR);

        sol_try (merak_vector_len(lhs, &llen));
        sol_try (merak_vector_len(rhs, &rlen));
        *gt = sol_float_gt(llen, rlen, FLOAT_EPSILON);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




        /* implement the merak_vector_add() interface function; we add two
         * vectors by adding their individual components */
extern sol_erno merak_vector_add(merak_vector *lhs, const merak_vector *rhs)
{
SOL_TRY:
        sol_assert (lhs && rhs, SOL_ERNO_PTR);

        lhs->x += rhs->x;
        lhs->y += rhs->y;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




        /* implement the merak_vector_sub() interface function; we subtract two
         * vectors by subtracting their individual components */
extern sol_erno merak_vector_sub(merak_vector *lhs, const merak_vector *rhs)
{
SOL_TRY:
        sol_assert (lhs && rhs, SOL_ERNO_PTR);

        lhs->x -= rhs->x;
        lhs->y -= rhs->y;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




        /* implement the merak_vector_mul() interface function; we multiply a
         * vector with a scalar by multiplying the individual components of the
         * former with the latter */
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




        /* implement the merak_vector_div() interface function; we divide a
         * vector with a scalar by dividing the individual components of the
         * former with the latter; we need to ensure that @scalar is non-zero */
extern sol_erno merak_vector_div(merak_vector *vec, const sol_float scalar)
{
SOL_TRY:
        sol_assert (vec, SOL_ERNO_PTR);
        sol_assert (!sol_float_eq(scalar, (sol_float) 0.0, FLOAT_EPSILON),
                    SOL_ERNO_RANGE);

        vec->x /= (sol_f32) scalar;
        vec->y /= (sol_f32) scalar;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 ******************************************************************************/

