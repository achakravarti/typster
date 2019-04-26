/******************************************************************************
 *                               MERAK LIBRARY
 *
 * File: merak/src/scene.c
 *
 * Description:
 *      This file is part of the internal implementation of the Merak Library.
 *      It implements the scene interface.
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




        /* define the `__merak_scene` struct; this struct was forward-declared
         * in the `merak/merak.h` header file */
struct __merak_scene {
        merak_scene_delegate *update; /* update delegate */
        merak_scene_delegate *render; /* render delegate */
        merak_scene_delegate *start;  /* start delegate */
        merak_scene_delegate *stop;   /* stop delegate */
        sol_size nref;                /* reference count */
};




        /* define the `delegate_default()` utility function; this function
         * serves as the placeholder callback for the scene update, render,
         * start, and stop functions; we're using this delegate so that we can
         * avoid a null condition check (since these delegates are optional) */
static sol_inline sol_erno delegate_default(merak_scene *scene)
{
        (void ) scene;
        return SOL_ERNO_NULL;
}




extern sol_erno merak_scene_new(merak_scene **scene,
                                merak_scene_delegate *update,
                                merak_scene_delegate *render,
                                merak_scene_delegate *start,
                                merak_scene_delegate *stop)
{
        auto merak_scene *hnd;

SOL_TRY:
        sol_try (sol_ptr_new((sol_ptr **) scene, sizeof (**scene)));
        hnd = *scene;
        hnd->nref = (sol_size) 1;

        hnd->update = update ? update : delegate_default;
        hnd->render = render ? render : delegate_default;
        hnd->start = start ? start : delegate_default;
        hnd->stop = stop ? stop : delegate_default;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_scene_copy(merak_scene **lhs, merak_scene *rhs)
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




extern void merak_scene_free(merak_scene **scene)
{
        auto merak_scene *hnd;

        if (sol_likely (scene && (hnd = *scene))) {
                if (!(--hnd->nref))
                        sol_ptr_free((sol_ptr **) scene);
        }
}




extern sol_erno merak_scene_update(merak_scene *scene)
{
SOL_TRY:
        sol_assert (scene, SOL_ERNO_PTR);

        scene->update(scene);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_scene_render(merak_scene *scene)
{
SOL_TRY:
        sol_assert (scene, SOL_ERNO_PTR);

        scene->render(scene);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_scene_start(merak_scene *scene)
{
SOL_TRY:
        sol_assert (scene, SOL_ERNO_PTR);

        scene->start(scene);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_scene_stop(merak_scene *scene)
{
SOL_TRY:
        sol_assert (scene, SOL_ERNO_PTR);

        scene->stop(scene);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

