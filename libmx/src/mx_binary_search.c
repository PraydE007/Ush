#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int start = 0;
    int end = size - 1;
    int midle;
    (*count) = 0;

    while (start <= end) {
        (*count)++;
        midle = (start + end) / 2;
        if (mx_strcmp(s, arr[midle]) > 0)
            start = midle + 1;
        else if (mx_strcmp(s, arr[midle]) < 0)
            end = midle - 1;
        else
            return midle;
    }
    (*count) = 0;
    return -1;
}
