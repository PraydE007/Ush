#include "../inc/ush.h"

// static char **command_matrix_creator(t_t_node **comn) {
//     t_t_node *pc = *comn;
//     int size = mx_tlist_len(comn);
//     int i = 0;
//     char **com_mat = NULL;

//     com_mat = (char **)malloc(sizeof(char *) * size);
//     com_mat[size] = NULL;
//     while (pc) {
//         if (strcmp(pc->text, " ") != 0) {
//             com_mat[i] = mx_strdup(pc->text);
//             i++;
//         }
//         pc = pc->next;
//     }
//     return com_mat;
// }

void mx_process_creator(char **command) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;

// int i = 0;
mx_printstr("command:\n");
// while (command[i]) {
mx_printstr(command[0]);
mx_printstr("\n");
// i++;
// }
    pid = fork();
    if (pid == 0) {
        if (getenv("PATH") != 0) {
            if (execvp(command[0], command) == -1)
                 perror("ush");
            exit(1);
        }
        else {
            if (execv(command[0], command) == -1)
                 perror("ush");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        perror("ush");
    }
    else if (pid > 0) {
        wpid = waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
            wpid = waitpid(pid, &status, WUNTRACED);
        }
    }
}
