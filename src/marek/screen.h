#if (!defined __MAREK_SCREEN)
#define __MAREK_SCREEN




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

extern int marek_shade_spawn(marek_shade **shade,
                             unsigned alpha,
                             unsigned red,
                             unsigned green,
                             unsigned blue);

extern void marek_shade_kill(marek_shade **shade);

extern int marek_shade_alpha(const marek_shade *shade, unsigned *alpha);

extern int marek_shade_red(const marek_shade *shade, unsigned *red);

extern int marek_shade_green(const marek_shade *shade, unsigned *green);

extern int marek_shade_blue(const marek_shade *shade, unsigned *blue);

extern int marek_shade_setalpha(marek_shade *shade, unsigned alpha);

extern int marek_shade_setred(marek_shade *shade, unsigned red);

extern int marek_shade_setgreen(marek_shade *shade, unsigned green);

extern int marek_shade_setblue(marek_shade *shade, unsigned blue);




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

extern int marek_screen_init(void);

extern void marek_screen_exit(void);

extern int marek_screen_clear(const marek_shade *shade);

extern int marek_screen_render(void);




#endif /* __MAREK_SCREEN */

