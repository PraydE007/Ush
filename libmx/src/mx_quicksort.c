#include "libmx.h"

static void quicksort_cycle(char **arr, int *left, int *right,
t_lints **data) {
    for ((*data)->i = (*left); (int)(*data)->i <= (*right); (*data)->i++) {
        if (mx_strlen(arr[(*data)->i]) > mx_strlen(arr[(*data)->pivot])
            || (*data)->i == (*data)->pivot) {
            (*data)->newL = (*data)->i;
            break;
        }
    }
    for ((*data)->j = (*right); (int)(*data)->j >= (*left); (*data)->j--) {
        if (mx_strlen(arr[(*data)->j]) < mx_strlen(arr[(*data)->pivot])
            || (*data)->j == (*data)->pivot) {
            (*data)->newR = (*data)->j;
            break;
        }
    }
}

static void quicksort_condition(char **arr, int *left, int *right,
t_lints **data) {

    quicksort_cycle(arr, left, right, data);
    if ((*data)->i == (*data)->pivot && (*data)->newR != (*data)->pivot) {
        (*data)->newL = (*data)->i;
        (*data)->pivot = (*data)->newR;
    }
    else if ((*data)->j == (*data)->pivot && (*data)->newL != (*data)->pivot) {
        (*data)->newR = (*data)->j;
        (*data)->pivot = (*data)->newL;
    }
}

int mx_quicksort(char **arr, int left, int right) {
    t_lints *data = mx_create_lintnode();

    data->pivot = (right - left) / 2 + left;
    data->newL = left;
    data->newR = right;

    for (; data->newL <= data->newR; data->newL++, data->newR--) {
        quicksort_condition(arr, &left, &right, &data);
        if (data->newL != data->newR) {
            mx_swap_str(&arr[data->newL], &arr[data->newR]);
            data->count++;
        }
    }
    data->newL = data->pivot + 1;
    data->newR = data->pivot - 1;
    if (left < (int)data->newR)
        data->count = data->count + mx_quicksort(arr, left, data->newR);
    if ((int)data->newL < right)
        data->count = data->count + mx_quicksort(arr, data->newL, right);
    return data->count;
}
