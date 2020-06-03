#include "../inc/ush.h"

static int strararrlen(char ***ararr) {
    int i = 0;
    int j = 0;

    if (ararr == NULL)
        return 0;
    while (ararr[i] != NULL) {
        for (int k = 0; ararr[i][k]; k++)
            j++;
        i++;
    }
    i--;
    return i + j;
}

char **mx_strararrdup(char ***strararr) {
    char **copy = NULL;
    int size = strararrlen(strararr);
    int k = 0;

    copy = (char **)malloc(sizeof(char *) * (size + 1));
    copy[size] = NULL;
    for (int i = 0; strararr[i]; i++) {
        for (int j = 0; strararr[i][j]; j++) {
            copy[k] = mx_strdup(strararr[i][j]);
            k++;
        }
        if (strararr[i + 1]) {
            copy[k] = mx_strdup("|");
            k++;
        }
    }
    if (copy == NULL)
        return NULL;
    return copy;
}
