/******************************************************************************
 *                               MERAK LIBRARY
 *
 * File: merak/src/vector.c
 *
 * Description:
 *      This file is part of the internal implementation of the Merak Library.
 *      It implements the keyboard manager interface.
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
#include <SDL2/SDL.h>




        /* declare the thread-local array of key states; we'll use this array to
         * store the key states as reported by SDL; we're initialising this
         * array to a null pointer to indicate that the keyboard manager hasn't
         * been initialised yet */
static sol_tls const sol_u8 *key_states = SOL_PTR_NULL;




        /* define the `merak_keyboard_init()` interface function; although not
         * required, we enforce the policy that a call to this function is
         * allowed only if the keyboard manager hasn't been initialised (as
         * determined by whether or not `key_states` is null); on
         * initialisation, we poll SDL for the current keyboard state */
extern sol_erno merak_keyboard_init(void)
{
SOL_TRY:
        sol_assert (!key_states, SOL_ERNO_STATE);

        key_states = SDL_GetKeyboardState(SOL_PTR_NULL);
        sol_assert (key_states, SOL_ERNO_STATE);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




        /* define the `merak_keyboard_exit()` interface function; by setting the
         * `key_states` thread-local variable to null, we indicate that the
         * keyboard manager has been released */
extern void merak_keyboard_exit(void)
{
        key_states = SOL_PTR_NULL;
}




        /* define the `merak_keyboard_state()` interface function; since there's
         * a one-to-one correspondence between the `MERAK_KEYBOARD_KEY`
         * enumerated values and the keyboard scan codes used by SDL (as both
         * follow the USB HID protocol), we can use the `key` argument as the
         * index of `key_states` */
extern sol_hot sol_erno merak_keyboard_state(const MERAK_KEYBOARD_KEY key,
                                             MERAK_KEYBOARD_STATE *state)
{
SOL_TRY:
        sol_assert (key_states, SOL_ERNO_STATE);
        sol_assert (state, SOL_ERNO_PTR);

        *state = key_states[key];

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




        /* define the `merak_keyboard_update()` interface function; we poll SDL
         * to determine the current keyboard state */
extern sol_hot sol_erno merak_keyboard_update(void)
{
SOL_TRY:
        sol_assert (key_states, SOL_ERNO_STATE);

        key_states = SDL_GetKeyboardState(SOL_PTR_NULL);
        sol_assert (key_states, SOL_ERNO_STATE);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 ******************************************************************************/

