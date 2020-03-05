NAME = ush

ROOT_A = libmx.a \

LIB_A = ./libmx/libmx.a \

HEADERS = ush.h \

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
	mx_slash_parse \
	mx_control_slash \
	mx_push_symbol \
	mx_break_on_error \
	mx_count_slashes \
	mx_one_slash \
	mx_two_slash \
	mx_three_slash \
	mx_one_slash_m \
	mx_two_slash_m \
	mx_parse_burnish \

INC_H = $(addprefix "inc/", $(HEADERS))

ROOT_C = $(addsuffix ".c", $(FILES))

SRC_C = $(addprefix "src/", $(ROOT_C))

ROOT_O = $(addsuffix ".o", $(FILES))

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -ltermcap

all: install

install:
	@make -C libmx install
	@cp $(SRC_C) .
	@cp $(INC_H) .
	@cp $(LIB_A) .
#	@clang $(CFLAGS) -c $(ROOT_C)
#	@clang $(CFLAGS) $(ROOT_O) $(ROOT_A) -o $(NAME)
	#TEST MODE
	@clang -c $(ROOT_C)
	@clang -ltermcap $(ROOT_O) $(ROOT_A) -o $(NAME)
	@mkdir -p obj
	@cp $(ROOT_O) obj/
	@rm -rf $(ROOT_O)

uninstall: clean
	@make -C libmx uninstall
	@rm -rf $(NAME)
	@rm -rf $(ROOT_A)

clean:
	@make -C libmx clean
	@rm -rf $(ROOT_O)
	@rm -rf $(ROOT_C)
	@rm -rf $(HEADERS)
	@rm -rf obj

reinstall: uninstall install
