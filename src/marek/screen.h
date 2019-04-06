#if (!defined __MAREK_SCREEN)
#define __MAREK_SCREEN


        /* initialises the screen */
int marek_screen_init(void);

        /* destroys the screen */
void marek_screen_exit(void);

        /* clears the screen */
int marek_screen_clear(void);

        /* renders the screen */
int marek_screen_render(void);

#endif /* __MAREK_SCREEN */

