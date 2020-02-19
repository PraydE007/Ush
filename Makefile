NAME = ush

ROOT_A = libmx.a \

LIB_A = ./libmx/libmx.a \

HEADERS = ush.h \

FILES = main

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
