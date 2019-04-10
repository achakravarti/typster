#if (!defined __MERAK_SCREEN)
#define __MERAK_SCREEN




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
 *      merak_shade represents an ARGB colour (= opacity + hue)
 *
 *      merak_shade_spawn() creates a new shade.
 *      merak_shade_kill() destroys an existing shade.
 *      merak_shade_alpha() gets alpha channel
 *      merak_shade_red() gets red channel
 *      merak_shade_green() gets green channel
 *      merak_shade_blue() gets blue channel
 *      merak_shade_setalpha() sets alpha channel
 *      merak_shade_setred() sets red channel
 *      merak_shade_setgreen() sets green channel
 *      merak_shade_setblue() sets blue channel
 */

typedef struct __merak_shade merak_shade;

extern sol_erno merak_shade_new(merak_shade **shade,
                                sol_word alpha,
                                sol_word red,
                                sol_word green,
                                sol_word blue);

extern void merak_shade_free(merak_shade **shade);

extern sol_erno merak_shade_alpha(const merak_shade *shade, sol_word *alpha);

extern sol_erno merak_shade_red(const merak_shade *shade, sol_word *red);

extern sol_erno merak_shade_green(const merak_shade *shade, sol_word *green);

extern sol_erno merak_shade_blue(const merak_shade *shade, sol_word *blue);

extern sol_erno merak_shade_setalpha(merak_shade *shade, sol_word alpha);

extern sol_erno merak_shade_setred(merak_shade *shade, sol_word red);

extern sol_erno merak_shade_setgreen(merak_shade *shade, sol_word green);

extern sol_erno merak_shade_setblue(merak_shade *shade, sol_word blue);




/*
 * Interface: point
 */

typedef struct __merak_point merak_point;

extern sol_erno merak_point_new(merak_point **point, sol_uint x, sol_uint y);

extern void merak_point_free(merak_point ** point);

extern sol_erno merak_point_x(const merak_point *point, sol_uint *x);

extern sol_erno merak_point_y(const merak_point *point, sol_uint *y);

extern sol_erno merak_point_setx(merak_point *point, sol_uint x);

extern sol_erno merak_point_sety(merak_point *point, sol_uint y);





/*
 * Interface: area
 */

typedef struct __merak_area merak_area;

extern sol_erno merak_area_new(merak_area **area,
                               sol_uint width,
                               sol_uint height);

extern void merak_area_free(merak_area **area);

extern sol_erno merak_area_width(const merak_area *area, sol_uint *width);

extern sol_erno merak_area_height(const merak_area *area, sol_uint *height);

extern sol_erno merak_area_setwidth(merak_area *area, sol_uint width);

extern sol_erno merak_area_setheight(merak_area *area, sol_uint height);




/*
 * Interface: screen
 *
 * Synopsis:
 *      #include "merak/merak.h"
 *
 *      void merak_screen_init(void);
 *      void merak_screen_exit(void);
 *      void merak_screen_clear(const merak_shade *shade);
 *      void merak_screen_render(void);
 *
 * Description:
 *      merak_screen_init() initialises the screen manager singleton.
 *      merak_screen_exit() destroys the screen manager.
 *      merak_screen_clear() clears the screen.
 *      merak_screen_render() renders the screen
 */

extern sol_erno merak_screen_init(const char *title,
                                  const merak_area *res,
                                  SOL_BOOL full);

extern void merak_screen_exit(void);

extern sol_erno merak_screen_brush(sol_ptr **brush);

extern sol_erno merak_screen_clear(const merak_shade *shade);

extern sol_erno merak_screen_render(void);




/*
 * Interface: game
 */
typedef sol_erno (merak_game_delegate)(void);

extern sol_erno merak_game_init(merak_game_delegate *input,
                                merak_game_delegate *update,
                                merak_game_delegate *render);

extern void merak_game_exit(void);

extern sol_erno merak_game_run(void);




/*
 * Interface: event
 */
typedef enum __MERAK_EVENT_CODE {
        MERAK_EVENT_CODE_IGNORED = -1,
        MERAK_EVENT_CODE_NULL = 0,
        MERAK_EVENT_CODE_QUIT
} MERAK_EVENT_CODE;

extern sol_erno merak_event_init(void);

extern void merak_event_exit(void);

extern sol_erno merak_event_poll(MERAK_EVENT_CODE *code);




/*
 * Interface: texture
 */

typedef struct __merak_texture merak_texture;

extern sol_erno merak_texture_new(merak_texture **tex, const char *fpath);

extern void merak_texture_free(merak_texture **tex);

extern sol_erno merak_texture_area(const merak_texture *tex, merak_area **area);

extern sol_erno merak_texture_render(const merak_texture *tex,
                                     const merak_point *loc);




#endif /* __MERAK_SCREEN */

