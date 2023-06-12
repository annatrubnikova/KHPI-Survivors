#include "../inc/list.h"

void mx_foreach_list(t_list *list, void (*f)(t_list *node)){
    if (list == NULL || f == NULL) return;
    for(t_list *tmp = list; tmp != NULL; tmp = tmp->next) {
        f(tmp);
    }
}
