#ifndef LIBMX_H
#define LIBMX_H

#include <unistd.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>

typedef struct  s_list {
    void  *data;
    struct s_list *next;
} t_list;

typedef struct  s_data {
    size_t i;
    int j;
    size_t buf_size;
    char delim;
    char *buf;
} t_data;

typedef struct  s_lints {
    unsigned int pivot ;
    unsigned int i;
    unsigned int j;
    unsigned int count;
    unsigned int newL;
    unsigned int newR;
} t_lints;

bool mx_isdigit(int c);
bool mx_isspace(char c);
char *mx_del_extra_spaces(const char *str);
char *mx_file_to_str(const char *file);
char *mx_itoa(long long number);
char *mx_nbr_to_hex(unsigned long nbr);
char *mx_replace_substr(const char *str, const char *sub,
const char *replace);
char *mx_spacedel(char *newstr, const char *str);
char *mx_strcat(char *s1, const char *s2);
char *mx_strcpy(char *dst, const char *src);
char *mx_strdup(const char *str);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_strjoin_free(char *s1, const char *s2);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strndup(const char *s1, size_t n);
char *mx_strnew(const int size);
char *mx_str_size_cpy(char *dst, const char *src, int start, int end);
char *mx_str_size_dup(const char *s1, size_t start, size_t end);
char *mx_str_size_dup_free(char *s1, size_t start, size_t end);
char **mx_strsplit(const char *s, char c);
char *mx_strstr(const char *haystack, const char *needle);
char *mx_strtrim(const char *str);
double mx_pow(double n, unsigned int pow);
int mx_atoi(const char *str);
int mx_count_substr(const char *str, const char *sub);
int mx_count_words(const char *str, char c);
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_bubble_sort(char **arr, int size);
int mx_get_char_index(const char *str, char c);
int mx_get_substr_allindex(const char *str, const char *subi, int count);
int mx_get_substr_index(const char *str, const char *subi);
int mx_list_size(t_list *list);
int mx_memcmp(const void *s1, const void *s2, size_t n);
int mx_nbrlen(int nbr);
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd);
int mx_quicksort(char **arr, int left, int right);
int mx_sqrt(int x);
int mx_strcmp(const char *s1, const char *s2);
int mx_strlen(const char *s);
t_data  *mx_create_datanode();
t_lints *mx_create_lintnode();
t_list *mx_create_node(void *data);
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));
unsigned long mx_hex_to_nbr(const char *hex);
void mx_del_strarr(char ***arr);
void mx_foreach(int *arr, int size, void (*f)(int));
void *mx_memccpy(void *restrict dst, const void *restrict src,
int c, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little,
size_t little_len);
void *mx_memmove(void *dst, const void *src, size_t len);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memset(void *b, int c, size_t len);
void mx_printchar(char c);
void mx_printint(int n);
void mx_printstr(const char *s);
void mx_print_strarr(char **arr, const char *delim);
void *mx_realloc(void *ptr, size_t size);
void mx_pop_front(t_list **head);
void mx_pop_back(t_list **head);
void mx_push_back(t_list **list, void *data);
void mx_push_front(t_list **list, void *data);
void mx_strdel(char **str);
void mx_str_reverse(char *s);
void mx_swap_char(char *s1, char *s2);
void mx_swap_str(char **s1, char **s2);
void mx_swap_u(unsigned int *i1, unsigned int *i2);
void mx_uarr_reverse(unsigned int *arr, int start, int size);

#endif
