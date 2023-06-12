#include "../inc/list.h"

static int list_size(t_list *list);

void mx_push_index(t_list **list, void *data, int index) {
    if (list == NULL) return;
    if (index == 0 || index < 0) {
        mx_push_front(list, data);
        return;
    }
    int len = list_size(*list);
    if (index >= len) {
        mx_push_back(list, data);
        return;
    }
    t_list *cur = *list;
    t_list *new = mx_create_node(data);
    int i = 0;
    while (cur != NULL && i <= index) {
        if (i == index) {
            new->next = cur->next;
            cur->next = new;
            return;
        }
        else 
            cur = cur->next;
        i++;
    }
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
