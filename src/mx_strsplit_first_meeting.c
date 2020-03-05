#include "../inc/ush.h"

char **mx_strsplit_first_meeting(const char *s, char c) {
    char **news = NULL;
    int i = 0;
    int start = 0;

    if (s == NULL)
        return NULL;
    news = (char **)malloc(sizeof(char **) * (2 + 1));
    for (; i < 3; i++)
        news[i] = NULL;
    i = 0;
    for (; s[i] != c; i++);
    start = i + 1;
    news[0] = mx_str_size_dup(s, 0, i);
    for (; s[i] != '\0'; i++);
    if (start != i)
        news[1] = mx_str_size_dup(s, start, i);
    return news;
}
