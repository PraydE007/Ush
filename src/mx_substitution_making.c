#include "../inc/ush.h"

static char ***command_for_substitution(t_ush *ush, char *substion) {
    char ***comforsub = NULL;
    
    comforsub = (char ***)malloc(sizeof(char **) * (2 + 1));
    comforsub[2] = NULL;;  
    comforsub[0] = (char **)malloc(sizeof(char *) * (3));
    comforsub[1] = (char **)malloc(sizeof(char *) * (2));
    comforsub[0][0] = mx_strdup("echo");
    if (mx_path_is(ush))
        comforsub[0][1] = mx_strdup(substion);
    else
        comforsub[0][1] = mx_strjoin("unset PATH;", substion);
    comforsub[0][2] = NULL;
    comforsub[1][0] = mx_strdup("zsh");
    comforsub[1][1] = NULL;
    return comforsub;
}

static void space_chenging(char **buf) {
    int size = 0;

    if ((*buf)) {
        size = mx_strlen((*buf));
        for (int i = 0; (*buf)[i]; i++) {
            if ((*buf)[i] == '\n' && (*buf)[i + 1])
                (*buf)[i] = ' ';
            else if ((*buf)[i] == '\n' && i == size - 1) {
                (*buf)[i] = '\0';
                size -= 1;
                (*buf) = (char *)realloc((*buf), size);
            }
        }
    }   
}

static void returning_char(char **buf, int *pipedes) {
    char *sub = mx_strnew(8192);
    int size = 0;
    int nothing = 0;

    close(pipedes[1]);
    read(pipedes[0], sub, 8192);
    if (sub) {
        while (sub[0] != '\0') {
            (*buf) = mx_strjoin_free((*buf), sub);
            mx_strdel(&sub);
            sub = mx_strnew(8192);
            read(pipedes[0], sub, 8192);
        }
    }
    space_chenging(buf);
    mx_strdel(&sub);
    close(pipedes[0]);
}

static void pipe_creator(t_ush *ush, char ***comforsub, char **buf,
                                                                int *pipedes) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    int pipedes2[2];
    int pipedes3[2];

    pipe(pipedes2);
    pipe(pipedes3);
    pid = fork();
    if (pid == 0) {
        dup2(pipedes[0], 0);
        mx_child_exvprocess(ush, pipedes2, pipedes3, comforsub[1]);
    }
    else if (pid < 0)
        perror("ush");
    else if (pid > 0 ) {
        mx_sub_error_printing(pipedes3);
        returning_char(buf, pipedes2);
        wpid = waitpid(pid, &status, WUNTRACED);
    }
}

char *mx_substitution_making(t_ush *ush, char *substion) {
    pid_t pid = 0;
    int pipedes[2];
    int pipedes2[2];
    char *buf = NULL;
    char ***comforsub = command_for_substitution(ush, substion);

    pipe(pipedes);
    pipe(pipedes2);
    pid = fork();
    if (pid == 0)
        mx_child_exvprocess(ush, pipedes, pipedes2, comforsub[0]);
    else if (pid < 0)
        perror("ush");
    else if (pid > 0 ) {
        close(pipedes[1]);
        pipe_creator(ush, comforsub, &buf, pipedes);
    }
    mx_del_strararr(&comforsub);
    return buf;
}
