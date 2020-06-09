NAME = ush

FILES = main \
	mx_adding_variable \
	mx_break_on_error \
	mx_buf_drop \
	mx_buf_push \
	mx_buf_safe_realloc \
	mx_cd \
	mx_cd_s \
	mx_cd_P \
	mx_change_color \
	mx_check_commands \
	mx_check_key_allow \
	mx_child_exvprocess \
	mx_child_process \
	mx_clone_blocks \
	mx_clone_history \
	mx_command_matrix_creator \
	mx_constant_variables \
	mx_control_slash \
	mx_cntrl_z_printing \
	mx_count_pipes \
	mx_count_slashes \
	mx_create_history_node \
	mx_create_block_node \
	mx_create_env_flags \
	mx_creat_jobs_node \
	mx_creat_pid_node \
	mx_creat_pwdilda_node \
	mx_create_termconf \
	mx_create_text_node \
	mx_create_ush \
	mx_creat_variable_node \
	mx_create_workaround \
	mx_del_clone_history \
	mx_dealloc_blocks \
	mx_dealloc_termconf \
	mx_dealloc_ush \
	mx_del_strararr \
	mx_dollar_parse \
	mx_doumrk_parse \
	mx_drop_n_char \
	mx_env_variable_checking \
	mx_error_making \
	mx_exit \
	mx_export \
	mx_export_matrix_creator \
	mx_fg \
	mx_fg_command_handler \
	mx_fg_signal \
	mx_four_slash \
	mx_four_slash_m \
	mx_four_slash_s \
	mx_four_slash_sinmrk \
	mx_get_buf_type \
	mx_get_history_last_str \
	mx_get_h_node_index \
	mx_get_last_h_node \
	mx_get_twidth \
	mx_get_variable \
	mx_have_equals \
	mx_history_handler \
	mx_init_clone \
	mx_is_builtin \
	mx_is_built_in \
	mx_is_command \
	mx_is_control_slash \
	mx_is_fg_command \
	mx_is_pipe \
	mx_is_slash \
	mx_isvariable \
	mx_jobs \
	mx_jobs_list_len \
	mx_jobs_sign_change \
	mx_key_value_creation \
	mx_one_slash \
	mx_one_slash_m \
	mx_one_slash_s \
	mx_one_slash_sinmrk \
	mx_open_tty \
	mx_path_is \
	mx_parse_block_pro \
	mx_parse_buf_pro \
	mx_parse_burnish_pro \
	mx_parser_cd \
	mx_pipe_matrix_creator \
	mx_pipe_parent_process \
	mx_pipe_process_creator \
	mx_pop_back_variable \
	mx_pop_block_front \
	mx_pop_front_pid \
	mx_pop_front_pwdilda \
	mx_pop_front_variable \
	mx_pop_h_node_front \
	mx_pop_jobs_node \
	mx_pop_specific \
	mx_pop_t_node_front \
	mx_print_history \
	mx_process_creator \
	mx_programm_finder \
	mx_pwd \
	mx_push_back_pid \
	mx_push_back_pwdilda \
	mx_push_back_variable \
	mx_push_block_back \
	mx_push_h_node_back \
	mx_push_jobs_node \
	mx_push_n_char \
	mx_push_symbol \
	mx_push_symbol_l \
	mx_push_t_node_back \
	mx_rd_print_color \
	mx_rd_print_pbc \
	mx_rd_print_old \
	mx_read_from_thread \
	mx_read_input_pro \
	mx_read_termconf \
	mx_replace_subst \
	mx_replace_tild \
	mx_replace_variables \
	mx_restore_buffer \
	mx_set_history_pos \
	mx_signal_end \
	mx_sig_init \
	mx_sinmrk_parse \
	mx_size_of_pipe_matstr \
	mx_sixteen_ez_fix \
	mx_slash_parse \
	mx_space_parse \
	mx_strararrdup \
	mx_strarrlen \
	mx_strcmp_export \
	mx_strsplit_first_meeting \
	mx_sub_error_printing \
	mx_subst_dol_parse \
	mx_substitution_making \
	mx_subst_parse \
	mx_subst_slash_parse \
	mx_term_width_check \
	mx_text_node_split \
	mx_text_parse \
	mx_three_slash \
	mx_three_slash_m \
	mx_three_slash_s \
	mx_three_slash_sinmrk \
	mx_tildastr \
	mx_tild_parse \
	mx_tlist_len \
	mx_two_slash \
	mx_two_slash_m \
	mx_two_slash_s \
	mx_two_slash_sinmrk \
	mx_unset \
	mx_variable_cleaning \
	mx_variable_list_len \
	mx_which \
	mx_which_str \
	mx_doumrk_subst \
	mx_replace_subst_nested \
	mx_doumrk_dollar \
	mx_replace_var_nested \
	mx_check_flags_echo \
	mx_echo \
	mx_one_slash_e \
	mx_two_slash_e \
	mx_three_slash_e \
	mx_four_slash_e \

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
	#RELEASE MODE
	@clang $(CFLAGS) -c $(SRC_COMPILE)
	@clang $(CFLAGS) -ltermcap $(OBJ) $(LIB_A) -o $(NAME)
#	TEST MODE
#	@clang -c $(SRC_COMPILE)
#	@clang -ltermcap $(OBJ) $(LIB_A) -o $(NAME)
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
