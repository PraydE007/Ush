#include "../inc/ush.h"
// CHECK IF WE NEED THIS FUNCTION
// static void pipe_split(t_ush *ush, char **command) {
//     char ***pipemat = mx_pipe_matrix_creation(ush, command);
//     int k = 0;

//     if (pipemat == NULL)
//         return NULL;
//     for (int i = 0; pipemat[i]; i++) {
//         for (int j = 0; pipemat[j]; j++) {
//             if (!mx_is_pipe(NULL, command[k])) {
//                 pipemat[i][j] = mx_strdup(command[k]);
//                 k++;
//             }
//         }
//     } 
// }

char ***mx_pipe_parsing(t_ush *ush, char **command) {
    char ***pipemat = mx_pipe_matrix_creation(ush, command);
    int k = 0;

    if (pipemat == NULL)
        return NULL;
    for (int i = 0; pipemat[i]; i++) {
        printf("i: %d\n", i);
        if (mx_strcmp(command[k], "|") == 0)
            k++;
        printf("k: %d\n", k);
        for (int j = 0; pipemat[i][j]; j++) {
             printf("j: %d\n", j);
            if (!mx_is_pipe(NULL, command[k])) {
                printf("command[%d]: ", k);
                printf("%s\n", command[k]);
                pipemat[i][j] = mx_strdup(command[k]);
                printf("pipemat[%d][%d]: ", i, j);
                printf("%s\n", pipemat[i][j]);
                k++;
            }
        }
    }


    //     for (int i = 0; i < size; i++) {
    //         if (str[i] == c && (str[i+1] != '\0' && str[i+1] != c))
    //             count++;
    //     }
    // if (str[0] != c)
    //     count++;
    return pipemat;
}
