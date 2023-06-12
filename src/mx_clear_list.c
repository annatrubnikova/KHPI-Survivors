#include "../inc/list.h"

void mx_clear_list(t_list **list) {
    if (list == NULL) return;
    t_list *head = *list;
    while(head != NULL) {
        t_list *tmp = head;
        head = head->next;
        free(tmp);
    }
    *list = NULL;
}

//int main(){}
