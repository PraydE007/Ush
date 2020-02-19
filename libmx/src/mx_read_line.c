#include "libmx.h"

static void pop_datanode(t_data **data) {

    if (*data != NULL) {
        mx_strdel(&(*data)->buf);
        free(*data);
        *data = NULL;
    }
}

static char *ptr_delim_checking(char **ptr, char delim) {
    char *lineptr = NULL;
    int j;

    j = mx_get_char_index(*ptr, delim);
    if (j == -1) {
        lineptr = mx_strdup(*ptr);
        mx_strdel(ptr);
    }
    else {
        lineptr = mx_strndup(*ptr,  j);
        if (ptr[j + 1])
            *ptr = mx_str_size_dup_free(*ptr, j + 1, (mx_strlen(*ptr)));
    }
    return lineptr;
}

static char *buf_to_lineptr(char *lineptr, char **buf, int index) {
    char *temp = NULL;

    temp = mx_strndup(*buf, index);
    lineptr = mx_strjoin_free(lineptr, temp);
    mx_strdel(&temp);
   
    return lineptr;
}

static int read_line_cycle(char **lineptr, t_data *n, char **ptr, const int fd) {

    while ((n->i = read(fd, n->buf, n->buf_size)) > 0) {
        n->j = mx_get_char_index(n->buf, n->delim);
        if (n->i < n->buf_size && n->j == -1) {
            *lineptr = buf_to_lineptr(*lineptr, &n->buf, n->i);
            mx_strdel(&n->buf);
            return -1;
        }
        else if (n->j == -1)
            *lineptr = mx_strjoin_free(*lineptr, n->buf);
        else if (n->j > -1) {
            *lineptr = buf_to_lineptr(*lineptr, &n->buf, n->j);
            if (n->buf[n->j + 1])
                (*ptr) = mx_str_size_dup(n->buf, n->j + 1, n->i);
            break;
        }
    }
    return ((n->i == 0 && n->j == -1) ? -1 : mx_strlen(*lineptr));
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    t_data *n = mx_create_datanode();
    int result;
    static char *ptr;

    if (read(fd, NULL, 0) < 0 || fd == -1)
        return -2;
    else if (*lineptr)
        mx_strdel(lineptr); 
    if (ptr != NULL) {
        *lineptr = ptr_delim_checking(&ptr, delim);
        if (ptr != NULL)
            return mx_strlen(*lineptr);
    }
    n->buf_size = buf_size;
    n->delim = delim;
    n->buf = mx_strnew(buf_size);
    result = read_line_cycle(lineptr, n, &ptr, fd);
    pop_datanode(&n);
    return result;
}
