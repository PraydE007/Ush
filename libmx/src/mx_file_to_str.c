#include "libmx.h"

static void printerr(const char *s) {
    write(2, s, mx_strlen(s));
}

static void existence_error(const char *file) {
    printerr("error: file ");
    printerr(file);
    printerr(" does not exist\n");
    exit(0);
}

static void empty_error(const char *file) {
    printerr("error: file ");
    printerr(file);
    printerr(" is empty\n");
    exit(0);
}
char *mx_file_to_str(const char *file) {
    int fd = open(file, O_RDONLY);
    int size = 0;
    char buf;
    char *str = NULL;

    if (fd < 0) {
        existence_error(file);
    }
    while (read(fd, &buf, 1))
        size++;
    close(fd);
    if (size <= 0) {
        empty_error(file); 
    }
    fd = open(file, O_RDONLY);
    str = mx_strnew(size);
    read(fd, str, size);
    close(fd);
    return str;
}
