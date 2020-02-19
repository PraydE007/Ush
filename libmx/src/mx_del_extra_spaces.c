#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    char *trims = NULL;
    char *news = NULL;
    int count = 0;
    int i = 0;
    int size;

    if (str == NULL)
        return NULL;
    trims = mx_strtrim(str);
    while (trims[i]) {
        if (mx_isspace(trims[i]) && mx_isspace(trims[i-1]))
            count++;
        i++;
    }
    size = mx_strlen(trims);
    news = mx_strnew(size - count);
    mx_spacedel(news, trims);
    mx_strdel(&trims);
    return news;    
}
