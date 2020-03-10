#include "../inc/ush.h"

int main(int argc, char *argv[]) {
    t_ush *ush = mx_create_ush();
    int exit_code = 0;

    if (getenv("PATH") == 0) {
        char **kv = mx_key_value_creation(ush, PATH_FR);
        mx_push_back_variable(&ush->variable_list, kv);
        mx_del_strarr(&kv);
    }
    // printf("%s\n", getenv("ls"));
    // extern char **environ;

    // mx_read_environment(&ush->export_list, environ);
    // if (isatty(0) == 0) {
    //     if (!mx_read_input(ush)) {
    //             if (mx_parse_buf(ush)) {
    //                 // line = mx_str_dbl_split(ush->buf, ' ', ';');
    //                 mx_check_commands(ush);
    //                 // mx_del_strarr(&line);
    //                 mx_dealloc_blocks(&(ush->blocks)); // DELETE ALL LISTS
    //                 // PROCESSES
    //             }
    //     }
    // }
    // else {
        char *termtype = mx_tildastr("~-");
        printf ("%s\n", termtype);
        while (ush->active) {
            if (!mx_read_input(ush)) {
                if (mx_parse_buf(ush)) {
                    // line = mx_str_dbl_split(ush->buf, ' ', ';');
                    mx_check_commands(ush);
                    // mx_del_strarr(&line);
                    mx_dealloc_blocks(&(ush->blocks)); // DELETE ALL LISTS
                    // PROCESSES
                }
                // if (!isatty(0)) // INPUT STUCK FIX
                //     ush->active = false;
            }
        
            while (ush->termconf->clone)
                mx_pop_h_node_front(&(ush->termconf->clone));
        }
    // }
// t_variable *list = ush->variable_list;
// while (list) {

//     printf ("%s=", list->key);
//     printf ("%s\n", list->value);
//     list = list->next;
// }
            // if (!isatty(0)) // INPUT STUCK FIX
            //     ush->active = false;
    
    exit_code = ush->exit_code;
    mx_dealloc_ush(&ush);
    system("leaks -q ush");
    return exit_code;
}
