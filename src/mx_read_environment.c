#include "../inc/ush.h"

static char **key_value_creation(char *environ) {
    char **kv = NULL;

    kv = mx_strsplit_first_meeting(environ, '=');
    return kv;
}
// CHECK IF WE NEED THIS FUCTION
void mx_read_environment(t_export **export_list, char **env) {
    char **kv = NULL;

    for (int i = 0; env[i]; i++) {
        kv = key_value_creation(env[i]);
        mx_push_back_export(export_list, kv);
        mx_del_strarr(&kv);
    }
    // for (int i = 0; environ[i]; i++) {
    //     mx_printstr(environ[i]);
    //     mx_printstr("\n");
    // }
    // setenv("WWWW", "GGG", 1);
    // printf("environ: \n");
    // int i = 0;
    // while (env[i]) {
    //     printf("%s\n", env[i]);
    // i++;
    // }
}
