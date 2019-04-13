#if (!defined __MERAK_SCREEN)
#define __MERAK_SCREEN




#include "../../../sol/inc/env.h"
#include "../../../sol/inc/error.h"
#include "../../../sol/inc/hint.h"
#include "../../../sol/inc/libc.h"
#include "../../../sol/inc/log.h"
#include "../../../sol/inc/prim.h"
#include "../../../sol/inc/ptr.h"
#include "../../../sol/inc/test.h"




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

typedef struct __merak_shade {
        sol_u8 red;
        sol_u8 green;
        sol_u8 blue;
        sol_u8 alpha;
} merak_shade;




/*
 * Interface: point
 */

typedef struct __merak_point {
        sol_u16 x;
        sol_u16 y;
} merak_point;




/*
 * Interface: area
 */

typedef struct __merak_area {
        sol_u16 width;
        sol_u16 height;
} merak_area;




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

typedef struct __merak_sprite merak_sprite;

extern sol_erno merak_texture_new(merak_texture **tex, const char *fpath);

extern void merak_texture_free(merak_texture **tex);

extern sol_erno merak_texture_area(const merak_texture *tex, merak_area *area);

extern sol_erno merak_texture_render(const merak_texture *tex,
                                     const merak_point *loc);

extern sol_erno merak_texture_draw(const merak_texture *tex,
                                   const merak_point *src,
                                   const merak_area *clip,
                                   const merak_point *dst);

extern sol_erno merak_sprite_new(merak_sprite **sprite,
                                 const char *fpath,
                                 sol_size nrow,
                                 sol_size ncol);

extern void merak_sprite_free(merak_sprite **sprite);

extern sol_erno merak_sprite_area(const merak_sprite *sprite,
                                  merak_area *area);

extern sol_erno merak_sprite_nframe(const merak_sprite *sprite,
                                    sol_size *nframe);

extern sol_erno merak_sprite_draw(const merak_sprite *sprite,
                                  sol_index row,
                                  sol_index col,
                                  const merak_point *loc);




#endif /* __MERAK_SCREEN */

