#include "../inc/ush.h"

bool mx_is_fg_command(char *jobs_name, char *command) {
    int size_command = mx_strlen(command);
    int size_jobs_name = mx_strlen(jobs_name);

printf("jobs_name: %s\n", jobs_name);
printf("command: %s\n", command);
    if (size_command > size_jobs_name)
        return false;
    else {
        for (int i = 0; i < size_command; i++) {
            if (command[i] != jobs_name[i])
                    return false;
        }
    }
    return true;
}
