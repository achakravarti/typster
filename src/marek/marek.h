#if (!defined __MAREK_SCREEN)
#define __MAREK_SCREEN




#include "sol/inc/env.h"
#include "sol/inc/error.h"
#include "sol/inc/hint.h"
#include "sol/inc/libc.h"
#include "sol/inc/log.h"
#include "sol/inc/prim.h"
#include "sol/inc/ptr.h"
#include "sol/inc/test.h"




/*
 * Interface: shade
 *
 * Description:
 *      marek_shade represents an ARGB colour (= opacity + hue)
 *
 *      marek_shade_spawn() creates a new shade.
 *      marek_shade_kill() destroys an existing shade.
 *      marek_shade_alpha() gets alpha channel
 *      marek_shade_red() gets red channel
 *      marek_shade_green() gets green channel
 *      marek_shade_blue() gets blue channel
 *      marek_shade_setalpha() sets alpha channel
 *      marek_shade_setred() sets red channel
 *      marek_shade_setgreen() sets green channel
 *      marek_shade_setblue() sets blue channel
 */

typedef struct __marek_shade marek_shade;

extern sol_erno marek_shade_spawn(marek_shade **shade,
                                  sol_word alpha,
                                  sol_word red,
                                  sol_word green,
                                  sol_word blue);

extern void marek_shade_kill(marek_shade **shade);

extern sol_erno marek_shade_alpha(const marek_shade *shade, sol_word *alpha);

extern sol_erno marek_shade_red(const marek_shade *shade, sol_word *red);

extern sol_erno marek_shade_green(const marek_shade *shade, sol_word *green);

extern sol_erno marek_shade_blue(const marek_shade *shade, sol_word *blue);

extern sol_erno marek_shade_setalpha(marek_shade *shade, sol_word alpha);

extern sol_erno marek_shade_setred(marek_shade *shade, sol_word red);

extern sol_erno marek_shade_setgreen(marek_shade *shade, sol_word green);

extern sol_erno marek_shade_setblue(marek_shade *shade, sol_word blue);




/*
 * Interface: screen
 *
 * Synopsis:
 *      #include "marek/marek.h"
 *
 *      void marek_screen_init(void);
 *      void marek_screen_exit(void);
 *      void marek_screen_clear(const marek_shade *shade);
 *      void marek_screen_render(void);
 *
 * Description:
 *      marek_screen_init() initialises the screen manager singleton.
 *      marek_screen_exit() destroys the screen manager.
 *      marek_screen_clear() clears the screen.
 *      marek_screen_render() renders the screen
 */

extern sol_erno marek_screen_init(void);

extern void marek_screen_exit(void);

extern sol_erno marek_screen_clear(const marek_shade *shade);

extern sol_erno marek_screen_render(void);




/*
 * Interface: game
 */
typedef sol_erno (marek_game_delegate)(void);

extern sol_erno marek_game_init(marek_game_delegate *input,
                                marek_game_delegate *update,
                                marek_game_delegate *render);

extern void marek_game_exit(void);

extern sol_erno marek_game_run(void);




/*
 * Interface: event
 */
typedef enum MAREK_EVENT_CODE {
        MAREK_EVENT_CODE_IGNORED = -1,
        MAREK_EVENT_CODE_NULL = 0,
        MAREK_EVENT_CODE_QUIT
} MAREK_EVENT_CODE;

extern sol_erno marek_event_init(void);

extern void marek_event_exit(void);

extern sol_erno marek_event_poll(MAREK_EVENT_CODE *code);




#endif /* __MAREK_SCREEN */

