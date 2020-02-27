#include "ush.h"

t_b_node *mx_parse_block(t_t_node **head) {
    t_t_node *p = (*head);
    // t_b_node *b_node = NULL; JUST REFORM AFTER PARSE
    t_t_node *array = NULL;
    char *buf = NULL;
    // int piv = 0;
    int len = mx_strlen(p->text);
    int i = 0;
    int ch = 0;

    while (p) {
        
        while (p->text[i] != '\0' && len >= i) {

            fprintf(stdout, "CO: %i, CH: %c\n", i, p->text[i]);

            ch = i;
            if (p->text[i] == '\'')
                buf = mx_sinmrk_parse(&(p->text[i]), &i);
            else if (p->text[i] == '\"')
                buf = mx_doumrk_parse(&(p->text[i]), &i);
            else
                buf = mx_text_parse(&(p->text[i]), &i);

            //mx_printstr(" | ");

            if (buf) {
                mx_push_t_node_back(&array, buf);
                buf = NULL;
            }
            else {
                fprintf(stderr, MX_PIZDA, p->text[ch]);
                exit(666);
            }

            i++;
        }

        i = 0;
        t_t_node *x = array;
        while (x != NULL) {
            mx_printstr(x->text);
            mx_printstr("\n");
            x = x->next;
        }
        array = NULL;
        p = p->next;
    }
    return NULL;
}
