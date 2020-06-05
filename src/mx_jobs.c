#include "../inc/ush.h"

void mx_jobs(t_ush *ush) {
    t_jobs *pl = ush->jobs_list;
    char *number = NULL;

    while (pl != NULL) {
        mx_printstr("[");
        number = mx_itoa(pl->number);
        mx_printstr(number);
        mx_printstr("]  ");
        mx_printchar(pl->sign);
        mx_printstr(" suspended  ");
        for (int i = 0; pl->name[i]; i++) {
            mx_printstr(pl->name[i]);
            mx_printstr(" "); 
        }
char *serial_number = mx_itoa(pl->serial_number);
mx_printstr("   "); 
mx_printstr(serial_number);
mx_strdel(&serial_number);
        mx_strdel(&number);
        mx_printstr("\n");
        pl = pl->next;
    }
    ush->exit_code = 0;
}
