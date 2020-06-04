#include "../inc/ush.h"

bool mx_is_command(char *path, bool *flag, int index) {
    struct stat lt;

    if (stat(path, &lt) != -1) {
        if ((lt.st_mode & S_IXUSR) == S_IXUSR) {
            if (!index) {
                if (flag[1]) {
                    return true;
                }
                mx_printstr(path);
                mx_printchar('\n');
            }
            return true;
        }
    }
    return false;
}
