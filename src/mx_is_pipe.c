#include "../inc/ush.h"

bool mx_is_pipe(char **command, char *comstr) {
    if (command != NULL) {
        for (int i = 0; command[i]; i++) {
            if (mx_strcmp(command[i], "|") == 0)
                return true;
            for (int j = 0; command[i][j]; j++) {
                if (command[i][j] == '|')
                    return true;
            }
        }
    }
    else if (comstr != NULL) {
        for (int i = 0; comstr[i]; i++) {
            if (comstr[i] == '|')
                return true;
        }
    }
    return false;
}
