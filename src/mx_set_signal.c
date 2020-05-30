#include "../inc/ush.h"

void mx_set_signal(void) {
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    setpgid(0, 0);
}
