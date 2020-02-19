#include "libmx.h"

t_lints *mx_create_lintnode() {
    t_lints *node = (t_lints *)malloc(sizeof(t_lints));

    if (node) {
    node->pivot = 0;
    node->i = 0;
    node->j = 0;
    node->count = 0;
    node->newL = 0;
    node->newR = 0;
    }
    return node;    
}
