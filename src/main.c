#include "../inc/ush.h"

int main(int argc, char *argv[]) {
    t_ush *ush = mx_create_ush();
    int exit_code = 0;
// char *buf = NULL;
// int store = 0;
// buf = getenv("SHLVL");
// store = mx_atoi(buf);
// // mx_strdel(&buf);
//     if (!isatty(0)) {
//         store++;
//         buf = mx_itoa(store);
//         setenv("SHLVL", buf, 1);
//         mx_strdel(&buf);
//     }

    // if (getenv("PATH") == 0) {
    //     char **kv = mx_key_value_creation(ush, PH);
    //     mx_push_back_variable(&ush->variable_list, kv);
    //     mx_del_strarr(&kv);
    // }

        // char *termtype = mx_tildastr("~-");
        // printf ("%s\n", termtype);
        while (ush->active) {
            if (!mx_read_input(ush)) {
                if (mx_parse_buf(ush)) {
                    mx_check_commands(ush);
                    mx_dealloc_blocks(&(ush->blocks)); // DELETE ALL LISTS
                    // PROCESSES
                }
                if (!isatty(0)) // INPUT STUCK FIX
                    ush->active = false;
            }
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
