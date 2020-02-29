#include "ush.h"

// static char **export_split(char *str) {
//     char **newstr = NULL;

//     newstr

// }

void  mx_export(t_export **export_list, char **command, char **env) {
    t_export *pex = *export_list;
                // setenv("DDDD", "", 1);
                // printf("env2222: \n");
                // int i = 0;
                // while (env[i]) {
                //     printf("%s\n", env[i]);
                //     i++;
                // }
    if (mx_strarrlen(command) == 1) {
        while (pex) {
            mx_printstr(pex->key);
            mx_printstr("=");
            if (pex->value)
                mx_printstr(pex->value);
            else
                mx_printstr("''");
            mx_printstr("\n");
            pex = pex->next;
        }
    }
    else {
        for (int i = 1; command[i]; i++) {
            // mx_push_back_env(command[i]);
            // t_env *env =  list->data;
            // env->key
            // ((t_env*)list->data)->key
        }
    }	
}
