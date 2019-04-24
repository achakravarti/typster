#if (!defined __MERAK_API)
#define __MERAK_API




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
 * Interface: vector
 *
 * Abstract:
 *      A vector in Merak is similar to the mathematical concept of a vector. It
 *      is a construct that represents both a magnitude along with a direction
 *      in 2D space. Using this definition, a vector can be used to represent a
 *      change in spatial orientation from a given location. A vector may also
 *      represent a point in 2D space as a change of given magnitude and
 *      direction from the origin.
 *
 *      A vector in Merak has the following properties:
 *        - an x co-ordinate,
 *        - a y co-ordinate, and
 *        - a length (magnitude)
 *
 *     Two vectors may be compared by comparing their lengths; thus two vectors
 *     are equal if their lengths are equal. A vector with a length of zero is
 *     called a null vector. A vector may be added and subtracted with another
 *     vector (called the velocity vector), resulting in a change in both
 *     magnitude and direction. A vector may be multiplied and divided by a
 *     scalar (magnitude), in which case there is only a change in the length,
 *     but not in the direction.
 *
 *     The normal form of a vector is a vector with the same direction, but with
 *     the inverse of its original magnitude as its length.
 *
 * Detail:
 *      A vector in Merak is represented by the opaque type `merak_vector`. The
 *      functions that form the interface for `merak_vector` return a `sol_erno`
 *      error code to indicate whether or not the operation succeeded. The
 *      notable exception to this is the `merak_vector_free()` function, which
 *      returns `void`, since it's a finalisation routine.
 *
 *      The first parameter of all the interface functions takes a handle to a
 *      `merak_vector` instance. A `merak_vector **` handle indicates that a new
 *      `merak_vector` instance will be created, a `merak_vector *` handle
 *      indicates that an existing instance will be modified, and a `const
 *      merak_vector *` handle indicates that an existing instance won't be
 *      modified.
 *
 *      Assumptions.
 *
 *      The interface for `merak_vector` provides four housekeeping functions.
 *      `merak_vector_new()` and `merak_vector_new2()` are responsible for
 *      creating a new `merak_vector` instance. The former initialises the newly
 *      created instance to a null vector, whereas the latter initialises the
 *      instance with specific coordinates. `merak_vector_copy()` creates a copy
 *      of an existing instance, and `merak_vector_free()` destroys an existing
 *      instance by releasing the resources allocated to it.
 *
 *      There are three accessor functions for a `merak_vector` instance.
 *      `merak_vector_x()` and `merak_vector_y()` get the x and y coordinates
 *      respectively of `merak_vector` instance, and `merak_vector_len()` gets
 *      length.
 *
 *      There are three mutator functions for a `merak_vector` instance.
 *      `merak_vector_setx()` and `merak_vector_sety()` set the x and y
 *      coordinates respectively of the instance, and `merak_vector_norm()`
 *      transforms the instance to its normal form.
 *
 *      There are seven operator functions for a `merak_vector` instance.
 *      `merak_vector_lt()`, `merak_vector_eq()`, and `merak_vector_gt()`
 *      compare, respectively, whether a `merak_vector` instance is less than,
 *      equal to, or greater than another instance. `merak_vector_add()` and
 *      `merak_vector_sub()` add and subtract respectively one instance with
 *      another. `merak_vector_mul()` and `merak_vector_div()` multiplies and
 *      divides respectively an instance with a scalar.
 */
typedef struct __merak_vector merak_vector;

extern sol_erno merak_vector_new(merak_vector **vec);

extern sol_erno merak_vector_new2(merak_vector **vec,
                                  const sol_float x,
                                  const sol_float y);

extern sol_erno merak_vector_copy(merak_vector **lhs, const merak_vector *rhs);

extern void merak_vector_free(merak_vector **vec);

extern sol_erno merak_vector_x(const merak_vector *vec, sol_float *x);

extern sol_erno merak_vector_y(const merak_vector *vec, sol_float *y);

extern sol_erno merak_vector_len(const merak_vector *vec, sol_float *len);

extern sol_erno merak_vector_setx(merak_vector *vec, const sol_float x);

extern sol_erno merak_vector_sety(merak_vector *vec, const sol_float y);

extern sol_erno merak_vector_norm(merak_vector *vec);

extern sol_erno merak_vector_lt(const merak_vector *lhs,
                                const merak_vector *rhs,
                                SOL_BOOL *lt);

extern sol_erno merak_vector_eq(const merak_vector *lhs,
                                const merak_vector *rhs,
                                SOL_BOOL *eq);

extern sol_erno merak_vector_gt(const merak_vector *lhs,
                                const merak_vector *rhs,
                                SOL_BOOL *gt);

extern sol_erno merak_vector_add(merak_vector *lhs, const merak_vector *rhs);

extern sol_erno merak_vector_sub(merak_vector *lhs, const merak_vector *rhs);

extern sol_erno merak_vector_mul(merak_vector *vec, const sol_float scalar);

extern sol_erno merak_vector_div(merak_vector *vec, const sol_float scalar);




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
 * Interface: keyboard
 * https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2
 */
typedef enum __MERAK_KEYBOARD_KEY {
        MERAK_KEYBOARD_KEY_NONE = 0x00,     /* No key pressed */
        MERAK_KEYBOARD_KEY_OVERFLOW = 0x01, /* Too many keys pressed */

        MERAK_KEYBOARD_KEY_A = 0x04, /* Keyboard a and A */
        MERAK_KEYBOARD_KEY_B = 0x05, /* Keyboard b and B */
        MERAK_KEYBOARD_KEY_C = 0x06, /* Keyboard c and C */
        MERAK_KEYBOARD_KEY_D = 0x07, /* Keyboard d and D */
        MERAK_KEYBOARD_KEY_E = 0x08, /* Keyboard e and E */
        MERAK_KEYBOARD_KEY_F = 0x09, /* Keyboard f and F */
        MERAK_KEYBOARD_KEY_G = 0x0a, /* Keyboard g and G */
        MERAK_KEYBOARD_KEY_H = 0x0b, /* Keyboard h and H */
        MERAK_KEYBOARD_KEY_I = 0x0c, /* Keyboard i and I */
        MERAK_KEYBOARD_KEY_J = 0x0d, /* Keyboard j and J */
        MERAK_KEYBOARD_KEY_K = 0x0e, /* Keyboard k and K */
        MERAK_KEYBOARD_KEY_L = 0x0f, /* Keyboard l and L */
        MERAK_KEYBOARD_KEY_M = 0x10, /* Keyboard m and M */
        MERAK_KEYBOARD_KEY_N = 0x11, /* Keyboard n and N */
        MERAK_KEYBOARD_KEY_O = 0x12, /* Keyboard o and O */
        MERAK_KEYBOARD_KEY_P = 0x13, /* Keyboard p and P */
        MERAK_KEYBOARD_KEY_Q = 0x14, /* Keyboard q and Q */
        MERAK_KEYBOARD_KEY_R = 0x15, /* Keyboard r and R */
        MERAK_KEYBOARD_KEY_S = 0x16, /* Keyboard s and S */
        MERAK_KEYBOARD_KEY_T = 0x17, /* Keyboard t and T */
        MERAK_KEYBOARD_KEY_U = 0x18, /* Keyboard u and U */
        MERAK_KEYBOARD_KEY_V = 0x19, /* Keyboard v and V */
        MERAK_KEYBOARD_KEY_W = 0x1a, /* Keyboard w and W */
        MERAK_KEYBOARD_KEY_X = 0x1b, /* Keyboard x and X */
        MERAK_KEYBOARD_KEY_Y = 0x1c, /* Keyboard y and Y */
        MERAK_KEYBOARD_KEY_Z = 0x1d, /* Keyboard z and Z */

        MERAK_KEYBOARD_KEY_1 = 0x1e, /* Keyboard 1 and ! */
        MERAK_KEYBOARD_KEY_2 = 0x1f, /* Keyboard 2 and @ */
        MERAK_KEYBOARD_KEY_3 = 0x20, /* Keyboard 3 and # */
        MERAK_KEYBOARD_KEY_4 = 0x21, /* Keyboard 4 and $ */
        MERAK_KEYBOARD_KEY_5 = 0x22, /* Keyboard 5 and % */
        MERAK_KEYBOARD_KEY_6 = 0x23, /* Keyboard 6 and ^ */
        MERAK_KEYBOARD_KEY_7 = 0x24, /* Keyboard 7 and & */
        MERAK_KEYBOARD_KEY_8 = 0x25, /* Keyboard 8 and * */
        MERAK_KEYBOARD_KEY_9 = 0x26, /* Keyboard 9 and ( */
        MERAK_KEYBOARD_KEY_0 = 0x27, /* Keyboard 0 and ) */

        MERAK_KEYBOARD_KEY_ENTER = 0x28,      /* Keyboard Enter */
        MERAK_KEYBOARD_KEY_ESC = 0x29,        /* Keyboard Escape */
        MERAK_KEYBOARD_KEY_BKSPACE = 0x2a,    /* Keyboard Backspace */
        MERAK_KEYBOARD_KEY_TAB = 0x2b,        /* Keyboard Tab */
        MERAK_KEYBOARD_KEY_SPACE = 0x2c,      /* Keyboard Spacebar */
        MERAK_KEYBOARD_KEY_MINUS = 0x2d,      /* Keyboard - and _ */
        MERAK_KEYBOARD_KEY_EQUAL = 0x2e,      /* Keyboard = and + */
        MERAK_KEYBOARD_KEY_LBRACE = 0x2f,     /* Keyboard [ and { */
        MERAK_KEYBOARD_KEY_RBRACE = 0x30,     /* Keyboard ] and } */
        MERAK_KEYBOARD_KEY_BKSLASH = 0x31,    /* Keyboard \ and | */
        MERAK_KEYBOARD_KEY_HASHTILDE = 0x32,  /* Keyboard Non-US # and ~ */
        MERAK_KEYBOARD_KEY_SEMICOLON = 0x33,  /* Keyboard ; and : */
        MERAK_KEYBOARD_KEY_APOSTROPHE = 0x34, /* Keyboard ' and " */
        MERAK_KEYBOARD_KEY_GRAVE = 0x35,      /* Keyboard ` and ~ */
        MERAK_KEYBOARD_KEY_COMMA = 0x36,      /* Keyboard , and < */
        MERAK_KEYBOARD_KEY_DOT = 0x37,        /* Keyboard . and > */
        MERAK_KEYBOARD_KEY_SLASH = 0x38,      /* Keyboard / and ? */
        MERAK_KEYBOARD_KEY_CAPSLOCK = 0x39,   /* Keyboard Caps Lock */

        MERAK_KEYBOARD_KEY_F1 = 0x3a,  /* Keyboard F1 */
        MERAK_KEYBOARD_KEY_F2 = 0x3b,  /* Keyboard F2 */
        MERAK_KEYBOARD_KEY_F3 = 0x3c,  /* Keyboard F3 */
        MERAK_KEYBOARD_KEY_F4 = 0x3d,  /* Keyboard F4 */
        MERAK_KEYBOARD_KEY_F5 = 0x3e,  /* Keyboard F5 */
        MERAK_KEYBOARD_KEY_F6 = 0x3f,  /* Keyboard F6 */
        MERAK_KEYBOARD_KEY_F7 = 0x40,  /* Keyboard F7 */
        MERAK_KEYBOARD_KEY_F8 = 0x41,  /* Keyboard F8 */
        MERAK_KEYBOARD_KEY_F9 = 0x42,  /* Keyboard F9 */
        MERAK_KEYBOARD_KEY_F10 = 0x43, /* Keyboard F10 */
        MERAK_KEYBOARD_KEY_F11 = 0x44, /* Keyboard F11 */
        MERAK_KEYBOARD_KEY_F12 = 0x45, /* Keyboard F12 */

        MERAK_KEYBOARD_KEY_SYSRQ = 0x46,      /* Keyboard Print Screen */
        MERAK_KEYBOARD_KEY_SCROLLLOCK = 0x47, /* Keyboard Scroll Lock */
        MERAK_KEYBOARD_KEY_PAUSE = 0x48,      /* Keyboard Pause */
        MERAK_KEYBOARD_KEY_INSERT = 0x49,     /* Keyboard Insert */
        MERAK_KEYBOARD_KEY_HOME = 0x4a,       /* Keyboard Home */
        MERAK_KEYBOARD_KEY_PAGEUP = 0x4b,     /* Keyboard Page Up */
        MERAK_KEYBOARD_KEY_DELETE = 0x4c,     /* Keyboard Delete */
        MERAK_KEYBOARD_KEY_END = 0x4d,        /* Keyboard End */
        MERAK_KEYBOARD_KEY_PAGEDOWN = 0x4e,   /* Keyboard Page Down */
        MERAK_KEYBOARD_KEY_RIGHT = 0x4f,      /* Keyboard Right Arrow */
        MERAK_KEYBOARD_KEY_LEFT = 0x50,       /* Keyboard Left Arrow */
        MERAK_KEYBOARD_KEY_DOWN = 0x51,       /* Keyboard Down Arrow */
        MERAK_KEYBOARD_KEY_UP = 0x52,         /* Keyboard Up Arrow */

        MERAK_KEYBOARD_KEY_NUMLOCK = 0x53,    /* Keyboard Num Lock and Clear */
        MERAK_KEYBOARD_KEY_KPSLASH = 0x54,    /* Keypad / */
        MERAK_KEYBOARD_KEY_KPASTERISK = 0x55, /* Keypad * */
        MERAK_KEYBOARD_KEY_KPMINUS = 0x56,    /* Keypad - */
        MERAK_KEYBOARD_KEY_KPPLUS = 0x57,     /* Keypad + */
        MERAK_KEYBOARD_KEY_KPENTER = 0x58,    /* Keypad Enter */
        MERAK_KEYBOARD_KEY_KP1 = 0x59,        /* Keypad 1 and End */
        MERAK_KEYBOARD_KEY_KP2 = 0x5a,        /* Keypad 2 and Down Arrow */
        MERAK_KEYBOARD_KEY_KP3 = 0x5b,        /* Keypad 3 and PageDn */
        MERAK_KEYBOARD_KEY_KP4 = 0x5c,        /* Keypad 4 and Left Arrow */
        MERAK_KEYBOARD_KEY_KP5 = 0x5d,        /* Keypad 5 */
        MERAK_KEYBOARD_KEY_KP6 = 0x5e,        /* Keypad 6 and Right Arrow */
        MERAK_KEYBOARD_KEY_KP7 = 0x5f,        /* Keypad 7 and Home */
        MERAK_KEYBOARD_KEY_KP8 = 0x60,        /* Keypad 8 and Up Arrow */
        MERAK_KEYBOARD_KEY_KP9 = 0x61,        /* Keypad 9 and Page Up */
        MERAK_KEYBOARD_KEY_KP0 = 0x62,        /* Keypad 0 and Insert */
        MERAK_KEYBOARD_KEY_KPDOT = 0x63,      /* Keypad . and Delete */

        MERAK_KEYBOARD_KEY_102ND = 0x64,      /* Keyboard Non-US \ and | */
        MERAK_KEYBOARD_KEY_COMPOSE = 0x65,    /* Keyboard Application */
        MERAK_KEYBOARD_KEY_POWER = 0x66,      /* Keyboard Power */
        MERAK_KEYBOARD_KEY_OPEN = 0x74,       /* Keyboard Execute */
        MERAK_KEYBOARD_KEY_HELP = 0x75,       /* Keyboard Help */
        MERAK_KEYBOARD_KEY_PROPS = 0x76,      /* Keyboard Menu */
        MERAK_KEYBOARD_KEY_FRONT = 0x77,      /* Keyboard Select */
        MERAK_KEYBOARD_KEY_STOP = 0x78,       /* Keyboard Stop */
        MERAK_KEYBOARD_KEY_AGAIN = 0x79,      /* Keyboard Again */
        MERAK_KEYBOARD_KEY_UNDO = 0x7a,       /* Keyboard Undo */
        MERAK_KEYBOARD_KEY_CUT = 0x7b,        /* Keyboard Cut */
        MERAK_KEYBOARD_KEY_COPY = 0x7c,       /* Keyboard Copy */
        MERAK_KEYBOARD_KEY_PASTE = 0x7d,      /* Keyboard Paste */
        MERAK_KEYBOARD_KEY_FIND = 0x7e,       /* Keyboard Find */
        MERAK_KEYBOARD_KEY_MUTE = 0x7f,       /* Keyboard Mute */
        MERAK_KEYBOARD_KEY_VOLUMEUP = 0x80,   /* Keyboard Volume Up */
        MERAK_KEYBOARD_KEY_VOLUMEDOWN = 0x81, /* Keyboard Volume Down */

        MERAK_KEYBOARD_KEY_LCTRL = 0xe0,  /* Keyboard Left Control */
        MERAK_KEYBOARD_KEY_LSHIFT = 0xe1, /* Keyboard Left Shift */
        MERAK_KEYBOARD_KEY_LALT = 0xe2,   /* Keyboard Left Alt */
        MERAK_KEYBOARD_KEY_LMETA = 0xe3,  /* Keyboard Left GUI */
        MERAK_KEYBOARD_KEY_RCTRL = 0xe4,  /* Keyboard Right Control */
        MERAK_KEYBOARD_KEY_RSHIFT = 0xe5, /* Keyboard Right Shift */
        MERAK_KEYBOARD_KEY_RALT = 0xe6,   /* Keyboard Right Alt */
        MERAK_KEYBOARD_KEY_RMETA = 0xe7,  /* Keyboard Right GUI */
} MERAK_KEYBOARD_KEY;

typedef enum __MERAK_KEYBOARD_STATE {
        MERAK_KEYBOARD_STATE_UP = 0,
        MERAK_KEYBOARD_STATE_DOWN
} MERAK_KEYBOARD_STATE;

extern sol_erno merak_keyboard_init(void);

extern void merak_keyboard_exit(void);

extern sol_erno merak_keyboard_state(const MERAK_KEYBOARD_KEY key,
                                     MERAK_KEYBOARD_STATE *state);

extern sol_erno merak_keyboard_update(void);




/*
 * Interface: texture
 */

typedef struct __merak_texture merak_texture;

typedef struct __merak_sprite merak_sprite;

extern sol_erno merak_texture_new(merak_texture **tex, const char *fpath);

extern sol_erno merak_texture_copy(merak_texture **lhs, merak_texture *rhs);

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

extern sol_erno merak_sprite_copy(merak_sprite **lhs, merak_sprite *rhs);


extern void merak_sprite_free(merak_sprite **sprite);

extern sol_erno merak_sprite_area(const merak_sprite *sprite,
                                  merak_area *area);

extern sol_erno merak_sprite_nframe(const merak_sprite *sprite,
                                    sol_size *nframe);

extern sol_erno merak_sprite_frame(const merak_sprite *sprite,
                                   sol_index *row,
                                   sol_index *col);

extern sol_erno merak_sprite_setframe(merak_sprite *sprite,
                                      sol_index row,
                                      sol_index col);

extern sol_erno merak_sprite_draw(const merak_sprite *sprite,
                                  const merak_point *pos);




/*
 * Interface: entity
 */

typedef struct __merak_entity merak_entity;

typedef sol_erno (merak_entity_delegate)(merak_entity *entity);

extern sol_erno merak_entity_new(merak_entity **entity,
                                 merak_sprite *sprite,
                                 merak_entity_delegate *update);

extern sol_erno merak_entity_new2(merak_entity **entity,
                                  merak_sprite *sprite,
                                  merak_entity_delegate *update,
                                  merak_entity_delegate *dispose);

extern sol_erno merak_entity_new3(merak_entity **entity,
                                  merak_sprite *sprite,
                                  merak_entity_delegate *update,
                                  merak_entity_delegate *dispose,
                                  merak_entity_delegate *draw);

extern sol_erno merak_entity_copy(merak_entity **lhs, merak_entity *rhs);

extern void merak_entity_free(merak_entity **entity);

extern sol_erno merak_entity_vec(const merak_entity *entity,
                                 merak_vector **vec);

extern sol_erno merak_entity_frame(const merak_entity *entity,
                                   sol_index *row,
                                   sol_index *col);

extern sol_erno merak_entity_setvec(merak_entity *entity,
                                    const merak_vector *vec);

extern sol_erno merak_entity_setframe(merak_entity *entity,
                                      sol_index row,
                                      sol_index col);

extern sol_erno merak_entity_move(merak_entity *entity,
                                  const merak_vector *velocity);

extern sol_erno merak_entity_update(merak_entity *entity);

extern sol_erno merak_entity_draw(merak_entity *entity);




/*
 * Interface: arena
 */

extern sol_erno merak_arena_init(void);

extern void merak_arena_exit(void);

extern sol_erno merak_arena_push(merak_entity *entity);

extern sol_erno merak_arena_update(void);

extern sol_erno merak_arena_draw(void);




/*
 * Interface: game
 */
typedef sol_erno (merak_game_delegate)(void);

extern sol_erno merak_game_init(merak_game_delegate *update,
                                merak_game_delegate *render);

extern void merak_game_exit(void);

extern sol_erno merak_game_run(void);




/*
 * Interface: event
 */
typedef enum __MERAK_EVENT_CODE {
        MERAK_EVENT_CODE_QUIT = 0,
        MERAK_EVENT_CODE_KEYUP,
        MERAK_EVENT_CODE_KEYDOWN
} MERAK_EVENT_CODE;

extern sol_erno merak_event_init(void);

extern void merak_event_exit(void);

extern sol_erno merak_event_register(const MERAK_EVENT_CODE event,
                                     merak_game_delegate *handler);

extern sol_erno merak_event_update(void);




#endif /* __MERAK_API */

