#include "libmx.h"

char *mx_strcat(char *s1, const char *s2) {
    char *p_s1 = s1 + mx_strlen(s1);
    int i = 0;
    int j = mx_strlen(s2);
    
    while(i < j) {
        *p_s1++ = s2[i];
        i++;
    } 
    *p_s1 = '\0';
    return s1;
} 
