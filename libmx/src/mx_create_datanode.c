#include "libmx.h"

t_data  *mx_create_datanode() {
    t_data *node = (t_data*)malloc(sizeof(t_data));

    if (node == NULL)
        return NULL;
    node->i = 0;
    node->j = 0;
    node->buf_size = 0;
    node->delim = '\0';
    node->buf = NULL;
    return node;    
}
