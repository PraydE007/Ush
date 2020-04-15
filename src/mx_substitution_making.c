#include "../inc/ush.h"

static char ***command_for_substitution(char *substion) {
    char ***comforsub = NULL;
    
    comforsub = (char ***)malloc(sizeof(char **) * (2 + 1));
    comforsub[2] = NULL;;  
    comforsub[0] = (char **)malloc(sizeof(char *) * (3));
    comforsub[1] = (char **)malloc(sizeof(char *) * (2));
    comforsub[0][0] = mx_strdup("echo");
    comforsub[0][1] = mx_strdup(substion);
    comforsub[0][2] = NULL;
    comforsub[1][0] = mx_strdup("zsh");
    comforsub[1][1] = NULL;
    return comforsub;
}

static void child_exvprocess(int *pipedes, int inout, char **command) {
    if (inout == 0) {
        close(pipedes[0]);
        dup2(pipedes[1], 1);
        close(pipedes[1]);
    }
    else if (inout == 1) {
        close(pipedes[1]);
        dup2(pipedes[0], 0);
        close(pipedes[0]);
    }
    if (execvp(command[0], command) == -1)
        perror("ush");
    exit(EXIT_FAILURE);
}

static void returning_char(char **buf, int *pipedes) {
    char *sub = mx_strnew(2048);

    close(pipedes[1]);
    read(pipedes[0], sub, 2048);
    while (sub[0] != '\0') {
        (*buf) = mx_strjoin_free((*buf), sub);
        mx_strdel(&sub);
        sub = mx_strnew(2048);
        read(pipedes[0], sub, 2048);
    }
    mx_strdel(&sub);
    close(pipedes[0]);
}

static void pipe_creator(char ***comforsub, char **buf, int *pipedes) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    int pipedes2[2];

    pipe(pipedes2);
    pid = fork();
    if (pid == 0) {
        dup2(pipedes[0], 0);
        child_exvprocess(pipedes2, 0, comforsub[1]);
    }
    else if (pid < 0)
        perror("ush");
    else if (pid > 0 ) {
        returning_char(buf, pipedes2);
        wpid = waitpid(pid, &status, WUNTRACED);
    }
}

char *mx_substitution_making(char *substion) {
    pid_t pid = 0;
    int pipedes[2];
    char *buf = NULL;
    char ***comforsub = command_for_substitution(substion);

    pipe(pipedes);
    pid = fork();
    if (pid == 0)
        child_exvprocess(pipedes, 0, comforsub[0]);
    else if (pid < 0)
        perror("ush");
    else if (pid > 0 ) {
        close(pipedes[1]);
        pipe_creator(comforsub, &buf, pipedes);
    }
    mx_del_strararr(&comforsub);
    return buf;
}