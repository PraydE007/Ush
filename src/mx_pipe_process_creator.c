#include "../inc/ush.h"

void mx_pipe_process_creator(char **line) {
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
        int pipedes[2];
        pipe(pipedes);
        pid = fork();
        if (pid == 0) {
            close(pipedes[0]);
            close(1);
            dup(pipedes[1]);
            close(pipedes[1]);
            if (execvp(line[0], line) == -1)
                perror("ush");
            // close(pipedes[1]);
            exit(EXIT_FAILURE);
        }
        else if (pid < 0) {
            perror("ush");
        }
        else if (pid > 0) {
            close(pipedes[1]);
            pid = fork();
            if (pid == 0) {
                // close(pipedes[0]);
            dup2(pipedes[0], 0);
            if (execvp(line2[0], line2) == -1)
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
            // close(pipedes[0]);
        }
        // 
        

    //     mx_pop_line(list);
    // }
}