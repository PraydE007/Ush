#include "../inc/libmx.h"

char *mx_strnew_x(const int size) {
    char *p_arr = NULL;
    int i = 0;

    if (size < 0) 
        return NULL;
    else
        p_arr = (char *)malloc(sizeof(char) * size);
    if (!p_arr)
        return NULL;
    for (i = 0; i < size; i++) {
        p_arr[i] = '\0';
    }
    p_arr[i] = '\0';
    return p_arr;
}
