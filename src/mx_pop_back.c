#include "../inc/list.h"

void mx_pop_back(t_list **list) {
    if (list == NULL) return;
    t_list *cur = *list;
    if (cur == NULL) return;
    
    if (cur->next == NULL) {
        free(cur);
        *list = NULL;
        return;
    }

    while (cur->next->next != NULL) 
        cur = cur->next;
    free(cur->next);
    cur->next  = NULL;
}

//int main() {}
