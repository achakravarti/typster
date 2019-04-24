#include "merak.h"




struct arena_list_node {
        merak_entity *elem;
        struct arena_list_node *next;
};




struct arena_list {
        struct arena_list_node *head;
        struct arena_list_node *tail;
        struct arena_list_node *curr;
        sol_size nelem;
};




static sol_tls struct arena_list *arena_entities = SOL_PTR_NULL;




extern sol_erno merak_arena_init(void)
{
SOL_TRY:
        sol_assert (!arena_entities, SOL_ERNO_STATE);

        sol_try (sol_ptr_new((sol_ptr **) &arena_entities,
                             sizeof (*arena_entities)));

        arena_entities->head = SOL_PTR_NULL;
        arena_entities->tail = SOL_PTR_NULL;
        arena_entities->curr = SOL_PTR_NULL;
        arena_entities->nelem = (sol_size) 0;

        sol_log_trace("arena initialised");

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void merak_arena_exit(void)
{
        auto struct arena_list_node *node;

        if (sol_likely (arena_entities)) {
                arena_entities->curr = arena_entities->head;

                while ((node = arena_entities->curr)) {
                        arena_entities->curr = arena_entities->curr->next;

                        merak_entity_free(&node->elem);
                        sol_ptr_free((sol_ptr **) &node);
                }
        }

        sol_ptr_free((sol_ptr **) &arena_entities);
        sol_log_trace("arena exited");
}




extern sol_erno merak_arena_push(merak_entity *entity)
{
        auto struct arena_list_node *node = SOL_PTR_NULL;

SOL_TRY:
        sol_assert (arena_entities, SOL_ERNO_STATE);
        sol_assert (entity, SOL_ERNO_PTR);

        sol_try (sol_ptr_new((sol_ptr **) &node, sizeof (*node)));
        node->elem = SOL_PTR_NULL;
        node->next = SOL_PTR_NULL;

        sol_try (merak_entity_copy(&node->elem, entity));

        if (!arena_entities->head)
                arena_entities->head = node;

        if (arena_entities->tail)
                arena_entities->tail->next = node;

        arena_entities->tail = node;
        arena_entities->nelem++;

SOL_CATCH:
        if (node) {
                merak_entity_free(&node->elem);
                sol_ptr_free((sol_ptr **) &node);
        }

        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_arena_update(void)
{
SOL_TRY:
        sol_assert (arena_entities, SOL_ERNO_STATE);

        arena_entities->curr = arena_entities->head;

        while (arena_entities->curr) {
                sol_try (merak_entity_update(arena_entities->curr->elem));
                arena_entities->curr = arena_entities->curr->next;
        }

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_arena_draw(void)
{
SOL_TRY:
        sol_assert (arena_entities, SOL_ERNO_STATE);

        arena_entities->curr = arena_entities->head;

        while (arena_entities->curr) {
                sol_try (merak_entity_draw(arena_entities->curr->elem));
                arena_entities->curr = arena_entities->curr->next;
        }

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

