#include "../inc/ush.h"

void mx_pop_specific(t_variable **list, int index) {
    t_variable *buf = *list;
    t_variable *temp = NULL;
    int size = mx_variable_list_len(list);

    if ((*list != NULL) && (list != NULL)) {
        if (size - 1 >= index) {
            if (index == 0)
                mx_pop_front_variable(list);
            else {
                while (index > 1) {
                    buf = buf->next;
                    index--;
                }
                temp = buf->next->next;
                free(buf->next->value);
                free(buf->next->key);
                free(buf->next);
                buf->next = temp;
            }
        }
    }
}
