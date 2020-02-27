#include "ush.h"

// static t_b_node *parse_by_spaces(t_t_node **head) {
//     t_t_node *p = (*head);
//     t_b_node *blocks = NULL;
//     char *t_part = NULL;

    
// }

void mx_parse_buf(t_ush *ush) {
    t_t_node *t_node = NULL;
    char *buf = mx_strdup(ush->buf);
    char *text = NULL;

    text = strtok(buf, ";");
    while (text != NULL) {
        mx_push_t_node_back(&t_node, text);
        text = strtok(NULL, ";");
    }
    // t_b_node *blocks = parse_by_spaces(&t_node); // parse block func
    mx_strdel(&buf);
}

// static void del_list(t_b_node **head) {
//     t_b_node *p = (*head);

//     while (p != NULL) {
//         if (&(p->tokens))
//             mx_del_strarr(&(p->tokens));
//         mx_pop_block_front(&p);
//     }
// }

// static void redirect_strings(t_b_node **head, char **array) {
//     t_b_node *p = (*head);
//     int i = 0;

//     while (p != NULL) {
//         array[i] = p->tokens[0];
//         i++;
//         p = p->next;
//     }
// }

// static void parse_by_spaces(t_b_node *head) {
//     t_b_node *block = head;
//     t_b_node *buf = NULL;
//     char **array = NULL;
//     int buf_c = 0;
//     char *token;

//     while (block != NULL) {
//         token = strtok(block->tokens[0], " ");

//         while (token != NULL) {
//             array = (char **)malloc(sizeof(char *) * 2);
//             array[1] = NULL;
//             array[0] = mx_strdup(token);
//             mx_push_block_back(&buf, array);
//             token = strtok(NULL, " ");
//         }

//         buf_c = mx_blocks_count(&buf);
//         fprintf(stdout, "%i\n", buf_c);

//         mx_del_strarr(&(block->tokens));
//         block->tokens = (char **)malloc(sizeof(char *) * (buf_c + 1));
//         block->tokens[buf_c] = NULL;

//         redirect_strings(&buf, block->tokens);
//         del_list(&buf);

//         // while (buf != NULL)
//         //     mx_pop_block_front(&buf);

//         block = block->next;
//     }
// }

// void mx_parse_buf(t_ush *ush) {
//     t_t_node *head = NULL;
//     char *buf = mx_strdup(ush->buf);
//     char *token;

//     token = strtok(buf, ";");
//     while (token != NULL) {
//         mx_push_t_node_back(&head, token);
//         token = strtok(NULL, ";");
//     }
//     parse_by_spaces(head);
//     mx_strdel(&buf);
//     del_list(&head);
// }
