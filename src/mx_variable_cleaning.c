#include "../inc/ush.h"

void mx_variable_cleaning(t_ush *ush, int *count) {
    int lenth = 0;

    lenth = mx_variable_list_len(&ush->variable_list);
    for (int j = 0; j < lenth && j < (*count); j++)
        mx_pop_back_variable(&ush->variable_list);
}
