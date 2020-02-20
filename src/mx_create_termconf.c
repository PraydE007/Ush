#include "ush.h"

t_termconf *mx_create_termconf() {
    t_termconf *termconf = (t_termconf *)malloc(sizeof(t_termconf));

    mx_read_termconf(termconf);
    return termconf;
}
