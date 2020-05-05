#include "../inc/ush.h"

static void signal_stub() {
}

void mx_sig_init(void) {
    signal(SIGINT, signal_stub);
    signal(SIGTSTP, signal_stub);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
}
