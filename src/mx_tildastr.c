#include "../inc/ush.h"

char *mx_tildastr(char *tilda) {
    char dir[256];
    char *adress;

    if (mx_strcmp(tilda, "~") == 0) 
        return adress = getenv("HOME");
    else if (mx_strcmp(tilda, "~+") == 0) {
        getcwd(dir, 256);
        char *s = mx_strdup(dir);
        return s;
    }
    else if (mx_strcmp(tilda, "~-") == 0)
        return 0;
    return 0;
}