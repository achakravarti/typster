#include "merak.h"




struct scene_list_node {
        merak_scene *scene;
        struct scene_list_node *next;
};




struct scene_list {
        struct scene_list_node *head;
        struct scene_list_node *tail;
        sol_size nelem;
};




static sol_tls struct scene_list *scene_elem = SOL_PTR_NULL;



extern sol_erno merak_fsm_init(void)
{
SOL_TRY:
        sol_assert (!scene_elem, SOL_ERNO_STATE);

        sol_try (sol_ptr_new((sol_ptr **) &scene_elem, sizeof (*scene_elem)));

        scene_elem->head = SOL_PTR_NULL;
        scene_elem->tail = SOL_PTR_NULL;
        scene_elem->nelem = (sol_size) 0;

        sol_log_trace("finite scene machine initialised");

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void merak_fsm_exit(void)
{
        auto struct scene_list_node *curr, *next;

        if (sol_likely (scene_elem)) {
                curr = scene_elem->head;

                while (curr) {
                        next = curr->next;

                        merak_scene_free(&curr->scene);
                        sol_ptr_free((sol_ptr **) &curr);

                        curr = next;
                }
        }

        sol_ptr_free((sol_ptr **) &scene_elem);
        sol_log_trace("finite scene machine exited");
}




extern sol_erno merak_fsm_push(merak_scene *scene)
{
        auto struct scene_list_node *node = SOL_PTR_NULL;

SOL_TRY:
        sol_assert (scene_elem, SOL_ERNO_STATE);
        sol_assert (scene, SOL_ERNO_PTR);

        sol_try (sol_ptr_new((sol_ptr **) &node, sizeof (*node)));
        node->scene = SOL_PTR_NULL;
        node->next = SOL_PTR_NULL;

        sol_try (merak_scene_copy(&node->scene, scene));

        if (!scene_elem->head)
                scene_elem->head = node;

        if (scene_elem->tail)
                scene_elem->tail->next = node;

        scene_elem->tail = node;
        scene_elem->nelem++;

        sol_try (merak_scene_start(scene));

SOL_CATCH:
        if (node) {
                merak_scene_free(&node->scene);
                sol_ptr_free((sol_ptr **) &node);
        }

        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_fsm_replace(merak_scene *scene)
{
SOL_TRY:
        sol_assert (scene_elem, SOL_ERNO_STATE);

        /* TODO: need to check scene ID */
        merak_fsm_pop();
        sol_try (merak_fsm_push(scene));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno merak_fsm_pop(void)
{
        register sol_index i;
        register struct scene_list_node *curr;

SOL_TRY:
        sol_assert (scene_elem, SOL_ERNO_STATE);

        if (scene_elem->tail) {
                (void) merak_scene_stop(scene_elem->tail->scene);
                merak_scene_free(&scene_elem->tail->scene);
                sol_ptr_free((sol_ptr **) &scene_elem->tail);

                curr = scene_elem->head;
                scene_elem->nelem--;

                for (i = (sol_index) 0; i < scene_elem->nelem; i++)
                        curr = curr->next;

                curr->next = SOL_PTR_NULL;
                scene_elem->tail = curr;
        }

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}

