#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    char *newp = (char *)malloc(sizeof(char) * size);
    char *p_ptr = (char *) ptr;

    if (ptr == NULL)
        return NULL;

    for (size_t i = 0; i < size; i++)
        newp[i] = p_ptr[i];
    
    return newp;
}
