CC := cc
CFLAGS := -Wall -Wextra
NAME := minishell

LIBFT := libft/libft.a
INCL := -I headers/

SRC :=			src/main.c \
				src/builtins/echo.c \
				src/builtins/echo_utils.c
				src/builtins/export.c \
				src/builtins/unset.c \
				src/builtins/cd.c \
				src/builtins/env.c \
				src/builtins/exit.c \
				src/builtins/builtin_utils.c \
				src/builtins/builtins.c \
				src/builtins/pwd.c \
				src/builtins/var_utils.c \
				src/parsing/split.c \
				src/parsing/parser_utils.c \
				src/utils/strings.c \
				src/utils/white_spaces.c \
				src/utils/errors.c \
				src/utils/quotes_handling.c \
				src/utils/free_stuff.c

OBJ := $(patsubst %.c, %.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(INCL) -lreadline

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
