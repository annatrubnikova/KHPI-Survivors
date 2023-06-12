#include "../inc/list.h"

static int list_size(t_list *list);

void mx_pop_index(t_list **list, int index) {
    if (list == NULL) return;
    if (index == 0 || index < 0) {
        mx_pop_front(list);
        return;
    }
    int len = list_size(*list);
    if (index >= len - 1) {
        mx_pop_back(list);
        return;
    }
    t_list *cur = *list;
    int i = 0;
    for (;i < index - 1; i++) cur = cur->next;

    t_list *tmp_del = cur->next;
    cur->next = cur->next->next;
    free(tmp_del);
}

//int main() {}

static int list_size(t_list *list) {
    if (list == NULL) return 0;
    int count = 0;
    t_list *tmp = list;
    while (tmp != NULL) {
        tmp = tmp->next;
        count++;
    }
    return count;
}
