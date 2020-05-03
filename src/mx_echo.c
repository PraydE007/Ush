#include "../inc/ush.h"

static void print_1_type(char *arr, int j, int i, int trig) {
    while (arr[j + i]) {
        if (arr[j] == '\\' && trig == 1)
            j++;
        mx_printchar(arr[j]);
        j++;
    }
}

static void print_2_type(char *arr) {
    int j = 1;

    while (arr[j + 1]) {
        if ((arr[j] == '\\' && arr[j + 1] != '\'')
            || (arr[j] == '\\' && arr[j + 1] != '"')) {
            mx_echo_func_for_slesh(arr, j + 1);
            j++;
        }
        else
            mx_printchar(arr[j]);
        j++;
    }
}

static void part1_of_cycle(char *arr, char *split) {
    if (arr[0] == '\'')
        print_1_type(split, 1, 1, 0);
    else if (arr[0] == '"')
        print_1_type(arr, 1, 1, 0);
    else
        print_1_type(arr, 0, 0, 1);
}

static void part2_of_cycle(char *arr) {
    if (arr[0] == '\'')
        print_2_type(arr);
    else if (arr[0] == '"') 
        print_2_type(arr);
    else
        print_1_type(arr, 0, 0, 0);
}

void mx_builtin_echo(char **arr, char *origin) {
    int i = 1;
    int point = 2;
    t_echo *echo = (t_echo *)malloc(sizeof(t_echo));
    char **split = mx_strsplit(origin, ' ');

    memset(echo, 0, sizeof(t_echo));
    i = mx_parser_4_echo(arr, echo);
    while (arr[i]) {
        if (echo->E)
            part1_of_cycle(arr[i], split[point]);
        else
            part2_of_cycle(arr[i]);
        if (mx_strlen_for_2star(arr) - i != 1)
            mx_printchar(32);
        i++;
        point++;
    }
    mx_del_strarr(&split);
    if (!echo->n)
        mx_printchar(10);
}
