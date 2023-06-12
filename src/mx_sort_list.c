#include "../inc/list.h"

t_list *mx_sort_list(t_list *list, bool (*cmp)(void *a, void *b)) {
    if (list == NULL || cmp == NULL) return list;
    bool is_unsorted = true;
    while (is_unsorted) {
        is_unsorted = false;
        for(t_list *tmp = list; tmp->next != NULL; tmp = tmp->next) {
            t_list *cur = tmp;
            t_list *nxt = tmp->next;
            if (cmp(cur->data, nxt->data)) {
                is_unsorted = true;
                void *tmp_data = cur->data;
                cur->data = nxt->data;
                nxt->data = tmp_data;
            }
        }
    }
    return list;
}

//int main() {}
