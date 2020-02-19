NAME = libmx.a

HEADERS = libmx.h \

FILES = mx_atoi \
	mx_binary_search \
	mx_bubble_sort \
	mx_count_substr \
	mx_count_words \
	mx_create_datanode \
	mx_create_lintnode \
	mx_create_node \
	mx_del_extra_spaces \
	mx_del_strarr \
	mx_file_to_str \
	mx_foreach \
	mx_get_char_index \
	mx_get_substr_allindex \
	mx_get_substr_index \
	mx_hex_to_nbr \
	mx_itoa \
	mx_isdigit \
	mx_islower \
	mx_isspace \
	mx_isupper \
	mx_list_size \
	mx_memccpy \
	mx_memcmp \
	mx_memchr \
	mx_memcpy \
	mx_memrchr \
	mx_memmem \
	mx_memmove \
	mx_memset \
	mx_nbr_to_hex \
	mx_nbrlen \
	mx_pop_back \
	mx_pop_front \
	mx_pow \
	mx_printchar \
	mx_printint \
	mx_printstr \
	mx_print_strarr \
	mx_print_unicode \
	mx_push_back \
	mx_push_front \
	mx_quicksort \
	mx_read_line \
	mx_realloc \
	mx_replace_substr \
	mx_sort_list \
	mx_spacedel \
	mx_sqrt \
	mx_str_reverse \
	mx_str_size_cpy \
	mx_str_size_dup \
	mx_str_size_dup_free \
	mx_strcat \
	mx_strcmp \
	mx_strcpy \
	mx_strdel \
	mx_strdup \
	mx_strjoin \
	mx_strjoin_free \
	mx_strlen \
	mx_strncpy \
	mx_strndup \
	mx_strnew \
	mx_strsplit \
	mx_strstr \
	mx_strtrim \
	mx_swap_char \
	mx_swap_str \

INC_H = $(addprefix "inc/", $(HEADERS))

ROOT_C = $(addsuffix ".c", $(FILES))

SRC_C = $(addprefix "src/", $(ROOT_C))

ROOT_O = $(addsuffix ".o", $(FILES))

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@cp $(SRC_C) .
	@cp $(INC_H) .
	@clang $(CFLAGS) -c $(ROOT_C)
	@mkdir -p obj
	@cp $(ROOT_O) obj/
	@ar -rc $(NAME) $(ROOT_O)
	@rm -rf $(ROOT_O)

uninstall: clean
	@rm -rf $(NAME)

clean:
	@rm -rf $(ROOT_C)
	@rm -rf $(HEADERS)
	@rm -rf obj

reinstall: uninstall install
