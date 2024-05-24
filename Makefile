CC := cc
CFLAGS := -fsanitize=address -g -Wall -Wextra -Werror
NAME := minishell

LIBFT := libft/libft.a
INCL := -I headers/
RL_PATH := ~/.brew/opt/readline/lib

SRC :=			src/main.c \
				src/builtins/echo.c \
				src/builtins/echo_utils.c \
				src/builtins/export.c \
				src/builtins/export_utils.c \
				src/builtins/unset.c \
				src/builtins/cd.c \
				src/builtins/env.c \
				src/builtins/exit.c \
				src/builtins/builtin_utils.c \
				src/builtins/builtins.c \
				src/builtins/shelllevel.c \
				src/builtins/pwd.c \
				src/builtins/var_utils.c \
				src/parsing/split.c \
				src/parsing/parser.c \
				src/parsing/file_list_utils.c \
				src/parsing/parser_utils.c \
				src/parsing/arg_lst.c \
				src/parsing/cleaning.c \
				src/utils/strings.c \
				src/utils/white_spaces.c \
				src/utils/errors.c \
				src/utils/quotes_handling.c \
				src/utils/free_stuff.c \
				src/utils/init_c_env.c \
				src/execution/execute_commands.c \
				src/execution/execution_utils.c \
				src/ctrls/ctrld.c \
				src/ctrls/ctrl_utils.c

OBJ := $(patsubst %.c, %.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(INCL) -lreadline -L $(RL_PATH)

$(LIBFT):
	make -C ./libft

clean:
	rm -rf $(OBJ)
	make -C ./libft/ clean

fclean: clean
	make -C ./libft/ fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re		
