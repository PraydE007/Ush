#include "../inc/ush.h"

static void variable_cleaning(t_ush *ush, int *count) {
    int lenth = 0;

    lenth = mx_variable_list_len(&ush->variable_list);
    for (int j = 0; j < lenth && j < (*count); j++)
        mx_pop_back_variable(&ush->variable_list);
}

static void variable_error_printing(t_ush *ush, char *comn, int *count) {
    mx_printerr("ush: command not found: ");
    mx_printerr(comn);
    mx_printerr("\n");
    variable_cleaning(ush, count);
}

void mx_adding_variable(t_ush *ush, char **command, char **kv) {
    char **k_v2 = NULL;
    int count = 0;
    int lenth = 0;

    mx_push_back_variable(&ush->variable_list, kv);
    count++;
    for (int i = 1; command[i]; i++) {
        k_v2 = mx_key_value_creation(ush, command[i]);
        if (k_v2 != NULL || ush->equals) {
            if (k_v2 != NULL ) {
                if (mx_check_key_allow(k_v2)) {
                    mx_push_back_variable(&ush->variable_list, k_v2);
                    count++;
                }
                else{
                    variable_error_printing(ush, command[i], &count);
                    mx_del_strarr(&k_v2);
                    break;
                }
            }
            else {
                mx_del_strarr(&k_v2);
                for (i += 1; command[i]; i++) {
                    k_v2 = mx_key_value_creation(ush, command[i]);
                    if (k_v2 == NULL)
                        variable_cleaning(ush, &count);
                    mx_del_strarr(&k_v2);
                }
                break;
            }
        }
        else
            variable_error_printing(ush, command[i], &count);
        mx_del_strarr(&k_v2);
    }
}
