#include "../inc/ush.h"

void mx_env_variable_checking(t_variable **list, char *command) {
    t_variable *pl = *list;

    if (getenv(command) == 0) {
        while (pl) {
            if (mx_strcmp(command, pl->key) == 0) {
                if (pl->value != NULL)
                    setenv(command, pl->value, 1);
                else
                    setenv(command, "", 1);
            }
            pl = pl->next;;
        }
    }
}
