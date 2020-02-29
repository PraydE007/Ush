#include "ush.h"

void mx_process_creator(char **line) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    char *line2[] = {"cat", "-e", NULL};
    int i = 0;
    // while (line[i]) {
    //     mx_printstr(line[i]);
    // mx_printstr("\n");
    // i++;
    // }
    // while (list) {
        pid = fork();
        if (pid == 0) {
            if (execvp(line[0], line) == -1)
                perror("ush");
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
        // 
        

    //     mx_pop_line(list);
    // }
}
