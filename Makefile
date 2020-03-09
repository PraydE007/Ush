NAME = ush

FILES = main \
	mx_adding_variable \
	mx_buf_drop \
	mx_buf_push \
	mx_check_commands \
	mx_check_key_allow \
	mx_command_matrix_creator\
	mx_create_block_node \
	mx_create_termconf \
	mx_create_text_node \
	mx_create_ush \
	mx_dealloc_blocks \
	mx_dealloc_termconf \
	mx_dealloc_ush \
	mx_doumrk_parse \
	mx_envnode_creation \
	mx_env_variable_checking \
	mx_exit \
	mx_export \
	mx_export_matrix_creator \
	mx_exportnode_creation \
	mx_get_buf_type \
	mx_get_twidth \
	mx_have_equals \
	mx_is_built_in \
	mx_is_command \
	mx_isvariable \
	mx_key_value_creation \
	mx_parse_buf \
	mx_parse_block \
	mx_pop_back_variable \
	mx_pop_block_front \
	mx_pop_front_export \
	mx_pop_front_variable \
	mx_pop_t_node_front \
	mx_process_creator \
	mx_push_block_back \
	mx_push_back_export \
	mx_push_back_variable \
	mx_push_t_node_back \
	mx_read_environment \
	mx_read_input \
	mx_read_termconf \
	mx_restore_buffer \
	mx_sinmrk_parse \
	mx_space_parse \
	mx_strarrlen \
	mx_strcmp_export \
	mx_strsplit_first_meeting \
	mx_term_width_check \
	mx_text_parse \
	mx_tlist_len \
	mx_unset \
	mx_variablenode_creation \
	mx_variable_list_len \
	mx_pop_specific \
	mx_env \
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
	mx_which \

SRC_PREFFIX = $(addprefix src/, $(FILES))

SRC_PREFFIX = $(addprefix src/, $(FILES))

HEADER = inc/ush.h

SRC_COMPILE = $(addsuffix .c, $(SRC_PREFFIX))

OBJ = $(addsuffix .o, $(FILES))

CFLAGS = -std=c11 -Werror -Wall -Wextra -Wpedantic

LIB_A = libmx/libmx.a

all: install

install: ush

ush : $(SRC_COMPILE) $(HEADER)
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
