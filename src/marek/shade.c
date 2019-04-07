#include <stdlib.h>
#include "screen.h"




struct __marek_shade {
        unsigned char alpha;
        unsigned char red;
        unsigned char green;
        unsigned char blue;
};




extern int marek_shade_spawn(marek_shade **shade,
                             unsigned alpha,
                             unsigned red,
                             unsigned green,
                             unsigned blue)
{
        auto marek_shade *ctx;

        if (!shade || *shade) {
                goto error;
        }

        if (!(*shade = malloc(sizeof (**shade)))) {
                goto error;
        }

        ctx = *shade;
        marek_shade_setalpha(ctx, alpha);
        marek_shade_setred(ctx, red);
        marek_shade_setgreen(ctx, green);
        marek_shade_setblue(ctx, blue);

        return 0;
error:
        return 1;
}




extern void marek_shade_kill(marek_shade **shade)
{
        if (shade && *shade) {
                free(*shade);
                *shade = NULL;
        }
}




extern int marek_shade_alpha(const marek_shade *shade, unsigned *alpha)
{
        if (!(shade && alpha)) {
                goto error;
        }

        *alpha = shade->alpha;

        return 0;
error:
        return 1;
}




extern int marek_shade_red(const marek_shade *shade, unsigned *red)
{
        if (!(shade && red)) {
                goto error;
        }

        *red = shade->red;

        return 0;
error:
        return 1;
}




extern int marek_shade_green(const marek_shade *shade, unsigned *green)
{
        if (!(shade && green)) {
                goto error;
        }

        *green= shade->green;

        return 0;
error:
        return 1;
}




extern int marek_shade_blue(const marek_shade *shade, unsigned *blue)
{
        if (!(shade && blue)) {
                goto error;
        }

        *blue = shade->blue;

        return 0;
error:
        return 1;
}




extern int marek_shade_setalpha(marek_shade *shade, unsigned alpha)
{
        if (!shade) {
                goto error;
        }

        shade->alpha = alpha;

        return 0;
error:
        return 1;
}




extern int marek_shade_setred(marek_shade *shade, unsigned red)
{
        if (!shade) {
                goto error;
        }

        shade->red = red;

        return 0;
error:
        return 1;
}




extern int marek_shade_setgreen(marek_shade *shade, unsigned green)
{
        if (!shade) {
                goto error;
        }

        shade->green = green;

        return 0;
error:
        return 1;
}




extern int marek_shade_setblue(marek_shade *shade, unsigned blue)
{
        if (!shade ) {
                goto error;
        }

        shade->blue = blue;

        return 0;
error:
        return 1;
}

