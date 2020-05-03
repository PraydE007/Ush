NAME = ush

FILES = main \
	mx_adding_variable \
	mx_buf_drop \
	mx_buf_push \
	mx_check_commands \
	mx_check_key_allow \
	mx_child_exvprocess \
	mx_child_process \
	mx_command_matrix_creator \
	mx_constant_variables \
	mx_count_pipes \
	mx_create_block_node \
	mx_create_env_flags \
	mx_creat_pwdilda_node \
	mx_create_termconf \
	mx_create_text_node \
	mx_create_ush \
	mx_creat_variable_node \
	mx_dealloc_blocks \
	mx_dealloc_termconf \
	mx_dealloc_ush \
	mx_del_strararr \
	mx_doumrk_parse \
	mx_env \
	mx_envnode_creation \
	mx_env_variable_checking \
	mx_error_making \
	mx_exit \
	mx_export \
	mx_export_matrix_creator \
	mx_exportnode_creation \
	mx_get_buf_type \
	mx_get_twidth \
	mx_have_equals \
	mx_is_builtin \
	mx_is_built_in \
	mx_is_command \
	mx_is_pipe \
	mx_is_slash \
	mx_isvariable \
	mx_key_value_creation \
	mx_path_is \
	mx_parse_buf \
	mx_parse_block \
	mx_pipe_matrix_creation \
	mx_pipe_parsing \
	mx_pop_back_variable \
	mx_pop_block_front \
	mx_pop_front_export \
	mx_pop_front_pwdilda \
	mx_pop_front_variable \
	mx_pop_t_node_front \
	mx_process_creator \
	mx_programm_finder \
	mx_push_block_back \
	mx_push_back_export \
	mx_push_back_pwdilda \
	mx_push_back_variable \
	mx_push_t_node_back \
	mx_read_environment \
	mx_read_input \
	mx_read_termconf \
	mx_restore_buffer \
	mx_sinmrk_parse \
	mx_size_of_matstr \
	mx_space_parse \
	mx_strarrlen \
	mx_strcmp_export \
	mx_strsplit_first_meeting \
	mx_term_width_check \
	mx_text_parse \
	mx_tildastr \
	mx_tlist_len \
	mx_unset \
	mx_variable_list_len \
	mx_pop_specific \
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
	mx_pipe_process_creator \
	mx_push_n_char \
	mx_drop_n_char \
	mx_change_color \
	mx_read_from_thread \
	mx_create_history_node \
	mx_push_h_node_back \
	mx_pop_h_node_front \
	mx_clone_history \
	mx_set_history_pos \
	mx_get_history_last_str \
	mx_which \
	mx_which_str \
	mx_clone_blocks \
	mx_open_tty \
	mx_outlst \
	mx_rd_print_color \
	mx_rd_print_pbc \
	mx_rd_print_old \
	mx_print_history \
	mx_dollar_parse \
	mx_replace_variables \
	mx_get_variable \
	mx_buf_safe_realloc \
	mx_sixteen_ez_fix \
	mx_sub_error_printing \
	mx_substitution_making \
	mx_tild_parse \
	mx_replace_tild \
	mx_subst_parse \
	mx_replace_subst \
	mx_subst_dol_parse \
	mx_text_node_split \

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
