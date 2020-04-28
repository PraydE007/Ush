#include "../inc/ush.h"
// CHECK IF WE NEED THIS FUNCTION
void mx_pipe_process_creator_secondaddition(t_ush *ush, char ***line) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    // char *line2[] = {"cat", "-e", NULL};
    int i = 1;
    // while (line[i]) {
    //     mx_printstr(line[i]);
    // mx_printstr("\n");
    // i++;
    // }
    
        int pipedes[2];
        pipe(pipedes);
        pid = fork();
        if (pid == 0) {
            close(pipedes[0]);
            close(1);
            dup(pipedes[1]);
            close(pipedes[1]);
            if (execvp(line[0][0], line[0]) == -1)
                perror("ush");
            // close(pipedes[1]);
            exit(EXIT_FAILURE);
        }
        else if (pid < 0) {
            perror("ush");
        }
        else if (pid > 0 ) {
            close(pipedes[1]);
            dup2(pipedes[0], 0);
            while (line[i]) {
                if (line[i + 1]) {
                    int pipedes2[2];
                    pipe(pipedes2);
                    pid = fork();
                    if (pid == 0) {
                        close(pipedes2[0]);
                        close(1);
                        dup(pipedes2[1]);
                        close(pipedes2[1]);
                        if (execvp(line[i][0], line[i]) == -1)
                            perror("ush");
                        // close(pipedes[1]);
                        exit(EXIT_FAILURE);
                    }
                    else if (pid < 0) {
                        perror("ush");
                    }
                    else if (pid > 0 ) {
                        close(pipedes2[1]);
                        dup2(pipedes2[0], 0);
                        if (execvp(line[i+1][0], line[i+1]) == -1)
                            perror("ush");wpid = waitpid(pid, &status, WUNTRACED);
                    }
                }
                else {
                    // close(1);
                
                    pid = fork();
                    if (pid == 0) {
                 // close(pipedes[1]);
                        if (execvp(line[i][0], line[i]) == -1)
                            perror("ush");
                        exit(EXIT_FAILURE);
                    }
                    else if (pid < 0) {
                        perror("ush");
                    }
                    else if (pid > 0 ) {
                        wpid = waitpid(pid, &status, WUNTRACED);
                        while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
                            wpid = waitpid(pid, &status, WUNTRACED);
                        }
                    }
                }
        // close(1);
        i++;
        
            }
            // close(pipedes[0]);
    //     mx_pop_line(list);
    }
    
    // ush->active = false;
}



#include "../inc/ush.h"

void mx_pipe_process_creator(t_ush *ush, char ***line) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    // char *line2[] = {"cat", "-e", NULL};
    int i = 1;
    // while (line[i]) {
    //     mx_printstr(line[i]);
    // mx_printstr("\n");
    // i++;
    // }
    int pipedes2[2];
       int pipedes[2];
        pipe(pipedes);
        pid = fork();
        if (pid == 0) {
            close(pipedes[0]);
            close(1);
            dup(pipedes[1]);
            close(pipedes[1]);
            if (execvp(line[0][0], line[0]) == -1)
                perror("ush");
            // close(pipedes[1]);
            exit(EXIT_FAILURE);
        }
        else if (pid < 0) {
            perror("ush");
        }
        else if (pid > 0 ) {
            close(pipedes[1]);
            
            while (line[i]) {
                pipe(pipedes2);
                pid = fork();
                if (line[i + 1]) {
                    dup2(pipedes[0], 0);
                    
                    
                    if (pid == 0) {

                        close(pipedes2[0]);
                        close(1);
                        dup(pipedes2[1]);
                        close(pipedes2[1]);
                        if (execvp(line[i][0], line[i]) == -1)
                            perror("ush");
                        // close(pipedes[1]);
                        exit(EXIT_FAILURE);
                    }
                    else if (pid < 0) {
                        perror("ush");
                    }
                    // else if (pid > 0 ) {
                    //     close(pipedes2[1]);
                    //     dup2(pipedes2[0], 0);
                    //     if (execvp(line[i+1][0], line[i+1]) == -1)
                    //         perror("ush");
                        
                    // }
                }
                else {
                    // close(1);
                close(pipedes2[1]);
                    dup2(pipedes2[0], 0);
                    pid = fork();
                    if (pid == 0) {
                 // close(pipedes[1]);
                        if (execvp(line[i][0], line[i]) == -1)
                            perror("ush");
                        exit(EXIT_FAILURE);
                    }
                    else if (pid < 0) {
                        perror("ush");
                    }
                    else if (pid > 0 ) {
                        wpid = waitpid(pid, &status, WUNTRACED);
                        while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
                            wpid = waitpid(pid, &status, WUNTRACED);
                        }
                    }
                }
        // close(1);
        i++;
        
            }
            // close(pipedes[0]);
    //     mx_pop_line(list);
    }
    
    // ush->active = false;
}

// void pipe_creator(char ***line, int *pipedes, int *i) {
//     pid_t pid = 0;
//     pid_t wpid = 0;
//     int status = 0;
//     // int pipedes[2];
//     int pipedes2[2];

// char *ci = NULL;    
//     (*i)++;
//     pid = fork();
//     if (pid == 0) {
//         close(pipedes[0]);
//         dup2(pipedes[1], 1);
//         close(pipedes[1]);
// mx_printerr("1d: ");
// ci = mx_itoa((*i));
// mx_printerr(ci);
// mx_printerr("\n");
//         if (execvp(line[(*i)][0], line[(*i)]) == -1)
//             perror("ush");
//         exit(EXIT_FAILURE);
//     }
//     else if (pid < 0)
//         perror("ush");
//     else if (pid > 0 ) {
//         close(pipedes[1]);
// //         if (line[(*i) + 3]) {
// //             pipe(pipedes2);
// //             pid = fork();
// //             if (pid == 0) {
// //                 dup2(pipedes[0], 0);
// //                 close(pipedes2[0]);
// //                 dup2(pipedes2[1], 1);
// //                 close(pipedes2[1]);
// // mx_printerr("2d(i + 3): ");
// // ci = mx_itoa((*i));
// // mx_printerr(ci);
// // mx_printerr("\n");
// //                 if (execvp(line[(*i) + 1][0], line[(*i) + 1]) == -1)
// //                     perror("ush");
// //                 exit(EXIT_FAILURE);
// //             }
// //             else if (pid < 0)
// //                 perror("ush");
// //             else if (pid > 0 ) {
// //                 close(pipedes2[1]);
// //                 dup2(pipedes2[0], 0);
// //                 (*i)++;
// // printf("3(i + 3): %d\n", (*i));
// //                 mx_pipe_process_creator(ush, line, pipedes2, i);
// //                 close(pipedes2[0]);
// //             }
// //         }
// //         else 
//         if (line[(*i) + 2]) {
//             pipe(pipedes2);
//             pid = fork();
//             if (pid == 0) {
//                 dup2(pipedes[0], 0);
//                 close(pipedes2[0]);
//                 dup2(pipedes2[1], 1);
//                 close(pipedes2[1]);
// mx_printerr("4d(i + 2): ");
// ci = mx_itoa((*i));
// mx_printerr(ci);
// mx_printerr("\n");
//                 if (execvp(line[(*i) + 1][0], line[(*i) + 1]) == -1)
//                     perror("ush");
//                 exit(EXIT_FAILURE);
//             }
//             else if (pid < 0)
//                 perror("ush");
//             else if (pid > 0) {
//                 close(pipedes2[1]);
//                 dup2(pipedes2[0], 0);
//                 i++;
//                 pipe_creator(line, pipedes2, i);
//                 close(pipedes2[0]);
//             }
//         }
//         else if (line[(*i) + 1]) {
//             pid = fork();
//             if (pid == 0) {
//                 dup2(pipedes[0], 0);
//                 close(pipedes[0]);
// mx_printerr("6d(i + 1): ");
// ci = mx_itoa((*i));
// mx_printerr(ci);
// mx_printerr("\n");
//                 if (execvp(line[(*i) + 1][0], line[(*i) + 1]) == -1)
//                     perror("ush");
//                 exit(EXIT_FAILURE);
//             }
//             else if (pid < 0)
//                 perror("ush");
//             else if (pid > 0)
//                 wpid = waitpid(pid, &status, WUNTRACED);
//         }
//     }
// }


void pipe_creator(char ***line, int *pipedes, int *i) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    // int pipedes[2];
    int pipedes2[2];

    (*i) = (*i) + 1;
    close(pipedes[1]);
    pipe(pipedes2);
    pid = fork();
    if (pid == 0) {
        dup2(pipedes[0], 0);
        close(pipedes[0]);
        if (line[(*i) + 1]) {
            close(pipedes2[0]);
            dup2(pipedes2[1], 1);
            close(pipedes2[1]);
        }
        if (execvp(line[(*i)][0], line[(*i)]) == -1)
            perror("ush");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
        perror("ush");
    else if (pid > 0) {
        if (line[(*i) + 1]) {
            // close(pipedes2[1]);
            // dup2(pipedes2[0], 0);
            pipe_creator(line, pipedes2, i);
            // close(pipedes2[0]);
        }
        else
            wpid = waitpid(pid, &status, WUNTRACED);
    }
}


void mx_pipe_process_creator(t_ush *ush, char ***line) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    int i = 0;
    int pipedes[2];
    int pipedes2[2];

    pipe(pipedes);
    pid = fork();
    if (pid == 0) {
        close(pipedes[0]);
        dup2(pipedes[1], 1);
        close(pipedes[1]);
        if (execvp(line[i][0], line[i]) == -1)
            perror("ush");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
        perror("ush");
    else if (pid > 0 ) {
        // close(pipedes[1]);
        pipe_creator(line, pipedes, &i);
        // pipe(pipedes2);
        // pid = fork()
        // if (pid == 0) {
        //     dup2(pipedes[0], 0);
        //     close(pipedes[0]);
        //     if (line[i + 2]) {
        //         close(pipedes2[0]);
        //         dup2(pipedes2[1], 1);
        //         close(pipedes2[1]);
        //     }
        //     if (execvp(line[i + 1][0], line[i + 1]) == -1)
        //         perror("ush");
        //     exit(EXIT_FAILURE);
        // }
        // else if (pid < 0)
        //     perror("ush");
        // else if (pid > 0) {
        //     if (line[i + 2]) {
        //         close(pipedes2[1]);
        //         dup2(pipedes2[0], 0);
        //         i++;
        //         pipe_creator(line, pipedes2, &i);
        //         close(pipedes2[0]);
        //     }
        //     else
        //         wpid = waitpid(pid, &status, WUNTRACED);
        // }
    }
}