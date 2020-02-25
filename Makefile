NAME = uls

INC = uls.h

SRC = main.c \
mx_append.c \
mx_check_flags.c \
mx_compare_time.c \
mx_compare.c \
mx_compare_size.c \
mx_create_and_append_dnode.c \
mx_errors.c \
mx_fill_c_widths.c \
mx_fill_file.c \
mx_fill_input.c \
mx_flags_basic.c \
mx_flags.c \
mx_free_wlists.c \
mx_free.c \
mx_get_dir_stat.c \
mx_get_f_stat.c \
mx_get_file.c \
mx_get.c \
mx_init_wlist.c \
mx_is_hidden.c \
mx_lists.c \
mx_new_file_stat.c \
mx_print_formatted_list.c \
mx_print_multi_column.c \
mx_print_stats.c \
mx_print.c \
mx_process.c \
mx_put.c \
mx_recursive.c \
mx_set_error.c \
mx_sort.c 

OBJ = main.o \
mx_append.o \
mx_check_flags.o \
mx_compare_size.o \
mx_compare_time.c \
mx_compare.c \
mx_create_and_append_dnode.o \
mx_errors.o \
mx_fill_c_widths.o \
mx_fill_file.o \
mx_fill_input.o \
mx_flags_basic.o \
mx_flags.o \
mx_free_wlists.o \
mx_free.o \
mx_get_dir_stat.o \
mx_get_f_stat.o \
mx_get_file.o \
mx_get.o \
mx_init_wlist.o \
mx_is_hidden.o \
mx_lists.o \
mx_new_file_stat.o \
mx_print_formatted_list.o \
mx_print_multi_column.o \
mx_print_stats.o \
mx_print.o \
mx_process.o \
mx_put.o \
mx_recursive.o \
mx_set_error.o \
mx_sort.o 

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@make -sC libmx
	@cp $(addprefix src/, $(SRC)) .
	@cp $(addprefix inc/, $(INC)) .
	@clang $(CFLAGS) -c $(SRC) -I $(INC)
	@clang $(CFLAGS) libmx/libmx.a $(OBJ) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJ) ./obj

uninstall: clean
	@make uninstall -sC libmx
	@rm -rf $(NAME)

clean:
	@make clean -sC libmx
	@rm -rf $(INC) $(SRC) ./obj

reinstall: uninstall install
