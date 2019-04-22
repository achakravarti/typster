#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "merak.h"




struct list_node {
        merak_entity *elem;
        struct list_node *next;
};




struct list {
        struct list_node *head;
        struct list_node *tail;
        struct list_node *curr;
        sol_size nelem;
};




struct game {
        merak_game_delegate *update;
        merak_game_delegate *render;
        struct list *entities;
};




static sol_tls struct game *game_inst = SOL_PTR_NULL;




static sol_erno list_new(struct list **list)
{
        auto struct list *hnd;

SOL_TRY:
        sol_assert (list, SOL_ERNO_PTR);

        sol_try (sol_ptr_new((sol_ptr **) list, sizeof (**list)));
        hnd = *list;

        hnd->head = SOL_PTR_NULL;
        hnd->tail = SOL_PTR_NULL;
        hnd->curr = SOL_PTR_NULL;
        hnd->nelem = (sol_size) 0;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




static void list_free(struct list **list)
{
        auto struct list *hnd;
        auto struct list_node *node;

        if (sol_likely (list && (hnd = *list))) {
                hnd->curr = hnd->head;

                while ((node = hnd->curr)) {
                        hnd->curr = hnd->curr->next;

                        merak_entity_free(&node->elem);
                        sol_ptr_free((sol_ptr **) &node);
                }

                sol_ptr_free ((sol_ptr **) list);
        }
}




static sol_erno list_push(struct list *list, merak_entity *elem)
{
        auto struct list_node *node = SOL_PTR_NULL;

SOL_TRY:
        sol_assert (list && elem, SOL_ERNO_PTR);

        sol_try (sol_ptr_new((sol_ptr **) &node, sizeof (*node)));

        node->elem = SOL_PTR_NULL;
        node->next = SOL_PTR_NULL;

        sol_try (merak_entity_copy(&node->elem, elem));

        if (!list->head)
                list->head = node;

        if (list->tail)
                list->tail->next = node;

        list->tail = node;
        list->nelem++;

SOL_CATCH:
        if (node) {
                merak_entity_free(&node->elem);
                sol_ptr_free((sol_ptr **) &node);
        }

        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




static sol_erno list_start(struct list *list)
{
SOL_TRY:
        sol_assert (list, SOL_ERNO_PTR);

        list->curr = list->head;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




static sol_erno list_next(struct list *list)
{
SOL_TRY:
        sol_assert (list, SOL_ERNO_PTR);

        list->curr = list->curr->next;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_game_init(merak_game_delegate *update,
                                merak_game_delegate *render)
{
        const int iflag = IMG_INIT_PNG;

SOL_TRY:
        sol_assert (update && render, SOL_ERNO_PTR);
        sol_assert (!game_inst, SOL_ERNO_STATE);

        sol_try (sol_ptr_new((sol_ptr **) &game_inst, sizeof (*game_inst)));
        game_inst->update = update;
        game_inst->render = render;

        game_inst->entities = SOL_PTR_NULL;
        sol_try (list_new(&game_inst->entities));

        sol_assert (SDL_Init(SDL_INIT_EVERYTHING) >= 0, SOL_ERNO_STATE);
        sol_assert ((IMG_Init(iflag) & iflag) == iflag, SOL_ERNO_STATE);

SOL_CATCH:
        sol_log_erno(sol_erno_get());
        sol_log_trace("Querying SDL for errors...");
        sol_log_error(SDL_GetError());
        sol_log_error(IMG_GetError());

SOL_FINALLY:
        return sol_erno_get();
}




extern void merak_game_exit(void)
{
        if (sol_likely (game_inst)) {
                list_free(&game_inst->entities);
                sol_ptr_free((sol_ptr **) &game_inst);

                SDL_Quit();
                IMG_Quit();

                exit(SOL_ERNO_NULL);
        }
}




extern sol_erno merak_game_register(merak_entity *entity)
{
SOL_TRY:
        sol_assert (entity, SOL_ERNO_PTR);
        sol_assert (game_inst, SOL_ERNO_STATE);

        sol_try (list_push(game_inst->entities, entity));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_game_run(void)
{
        auto struct list_node *curr;

SOL_TRY:
        sol_assert (game_inst, SOL_ERNO_STATE);

        while (SOL_BOOL_TRUE) {
                sol_try (merak_event_update());

                sol_try (game_inst->update());
                sol_try (list_start(game_inst->entities));

                while ((curr = game_inst->entities->curr)) {
                        sol_try (merak_entity_update(curr->elem));
                        sol_try (merak_entity_draw(curr->elem));

                        sol_try (list_next(game_inst->entities));
                }

                sol_try (game_inst->render());
                sol_try (list_start(game_inst->entities));

                while ((curr = game_inst->entities->curr)) {
                        sol_try (merak_entity_draw(curr->elem));
                        sol_try (list_next(game_inst->entities));
                }

                sol_try (merak_screen_render());
        }

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

