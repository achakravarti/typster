#if (!defined __TYPSTER_API)
#define __TYPSTER_API




#include "merak/merak.h"




/*
 * Interface: enemy
 */

typedef merak_entity typster_enemy;

extern sol_erno typster_enemy_new(typster_enemy **enemy);

extern void typster_enemy_free(typster_enemy **enemy);

#endif // __TYPSTER_API

