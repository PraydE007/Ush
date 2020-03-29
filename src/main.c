#include "../inc/ush.h"

int main(int argc, char *argv[]) {
    t_ush *ush = mx_create_ush();
    int exit_code = 0;

    mx_constant_variables(ush);
    while (ush->active) {
        if (!mx_read_input(ush))
            mx_parse_buf(ush);
        while (ush->termconf->clone)
            mx_pop_h_node_front(&(ush->termconf->clone));
    }

t_variable *list = ush->variable_list;
while (list) {
     printf ("%s=", list->key);
     printf ("%s\n", list->value);
     list = list->next;
 }

    exit_code = ush->exit_code;
    mx_dealloc_ush(&ush);
    system("leaks -q ush");
    return exit_code;
}
