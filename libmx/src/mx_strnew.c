#include "libmx.h"

char *mx_strnew(const int size) {
    char *p_arr = NULL;
    int i;

    if (size < 0) 
        return NULL;
    else
        p_arr = (char *) malloc(sizeof(char)*(size + 1));

    for (i = 0; i < size; i++) {
        p_arr[i] = '\0';
    }
    p_arr[i] = '\0';
    return p_arr;
}
