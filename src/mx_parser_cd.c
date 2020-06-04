#include "../inc/ush.h"

static void flags_trig(t_ush *ush, bool trig) {
    if (trig == 0) {
        mx_printerr("cd: string not in pwd: -\n");
        ush->exit_code = 1;
        ush->cd_flags->rip_42 = 1;
    }
    else if (trig == 1) {
        ush->cd_flags->minus = 1;
        ush->cd_flags->s = 0;
        ush->cd_flags->P = 0;
    }
}

static void main_part(char *command, t_ush *ush) {
    int j = 1;

    while (command[j]) {
        if (command[j] == 's')
            ush->cd_flags->s = 1;
        else if (command[j] == 'P') {
            if (!ush->cd_flags->s)
                ush->cd_flags->P = 1;
        }
        else {
            mx_printerr("cd: no such file or directory: ");
            mx_printerr(command);
            mx_printerr("\n");
            ush->exit_code= 1;
            ush->cd_flags->rip_42 = 1;
            break;
        }
        j++;
    }
}

int mx_parser_cd(char **command, t_ush *ush) {
    int i = 1;

    while (command[i]) {
        if (strcmp(command[i], "-") == 0 && command[i + 1]) {
            flags_trig(ush, 0);
            break;
        }
        if (strcmp(command[i], "-") == 0)
            flags_trig(ush, 1);
        else {
            if (command[i][0] == '-')
                main_part(command[i], ush);
            else
                break;
        }
        i++;
    }
    return i;
}
