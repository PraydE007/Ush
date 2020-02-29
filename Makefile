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
	mx_read_termconf \
	mx_strarrlen \

INC_H = $(addprefix "inc/", $(HEADERS))

ROOT_C = $(addsuffix ".c", $(FILES))

SRC_C = $(addprefix "src/", $(ROOT_C))

ROOT_O = $(addsuffix ".o", $(FILES))

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

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
	@clang $(ROOT_O) $(ROOT_A) -o $(NAME)
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
