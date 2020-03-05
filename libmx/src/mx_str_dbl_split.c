#include "../inc/libmx.h"

static char **splitcycle(const char *s, char **ns, char c, char b) {
    int i = 0;
    int k = 0;
    int start;
    int end;

    while (s[i]) {
        for (; ((s[i] == c || s[i] == b) && s[i] != '\0'); i++);
        start = i;
        for (; (s[i] != c && s[i] != b && s[i] != '\0'); i++);
        end = i;
        if (start != end) {
            ns[k] = mx_str_size_dup(s, start, end);
            k++;
        }
    }
    return ns;
}

char **mx_str_dbl_split(const char *s, char c, char b) {
    char **news = NULL;

    if (s == NULL)
        return NULL;
    news = (char **)malloc(sizeof(char **) * (mx_count_dbl_words(s, c, b) + 1));
    news[mx_count_dbl_words(s, c, b)] = NULL;
    news = splitcycle(s, news, c, b);
    return news;
}
