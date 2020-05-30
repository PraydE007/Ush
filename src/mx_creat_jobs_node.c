#include "../inc/ush.h"

t_jobs *mx_creat_jobs_node(void) {
    t_jobs *node = (t_jobs*)malloc(sizeof(t_jobs));

    if (node) {
    	node->pid = 0;
	    node->number = 0;
	    node->sign = '\0';
	    node->name = NULL;
    }
    return node;	
}
