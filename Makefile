NAME = ush

FILES = main \
		mx_check_commands \
        mx_create_termconf \
        mx_create_ush \
        mx_dealloc_termconf \
       	mx_dealloc_ush \
       	mx_envnode_creation \
       	mx_export \
       	mx_exportnode_creation \
       	mx_pop_front_export \
       	mx_pop_front_variable \
       	mx_process_creator \
		mx_push_back_export \
       	mx_read_environment \
       	mx_read_input \
		mx_get_twidth \
		mx_restore_buffer \
        mx_term_width_check \
        mx_buf_push \
        mx_buf_drop \
        mx_get_buf_type \
        mx_parse_buf \
        mx_create_block_node \
        mx_pop_block_front \
        mx_push_block_back \
        mx_lstlen \
        mx_create_text_node \
        mx_pop_t_node_front \
        mx_push_t_node_back \
        mx_sinmrk_parse \
        mx_doumrk_parse \
        mx_text_parse \
        mx_parse_block \
        mx_space_parse \
        mx_dealloc_blocks \
        mx_read_termconf \
        mx_strarrlen \
		
SRC_PREFFIX = $(addprefix src/, $(FILES))

HEADER = inc/ush.h

DEL_SRC = $(addsuffix .c, $(FILES))

SRC = $(addsuffix .c, $(SRC_PREFFIX))

SRC_COMPILE = $(addsuffix .c, $(SRC_PREFFIX))

OBJ = $(addsuffix .o, $(FILES))

CFLAGS = -std=c11 -Werror -Wall -Wextra -Wpedantic

LIB_A = libmx/libmx.a

all: install

install: uls

uls : $(SRC) $(INC)
	@make -C libmx install
#	@clang $(CFLAGS) -c $(SRC_COMPILE)
#	@clang $(CFLAGS) $(OBJ) $(LIB_A) -o $(NAME)
	#TEST MODE
	@clang -c $(SRC_COMPILE)
	@clang -ltermcap $(OBJ) $(LIB_A) -o $(NAME)
	@mkdir -p obj
	@cp $(OBJ) obj/
	@rm -rf $(OBJ)

uninstall: clean
	@make -C libmx uninstall
	@rm -rf $(NAME)

clean:
	@make -C libmx clean
	@rm -rf obj

reinstall: uninstall install
