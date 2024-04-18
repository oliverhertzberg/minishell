CC := cc
CFLAGS := -Wall -Wextra
NAME := minishell

LIBFT := libft/libft.a
INCL := -I headers/

SRC := 			src/main \
				src/builtins/echo \
				src/builtins/export_and_unset \
				src/builtins/pwd \
				src/builtins/var_utils \
				src/utils/strings \
				src/utils/white_spaces \

OBJ := $(SRC:=.o)

obj/%.o: $(SRC)
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(INCL) -lreadline

$(LIBFT):
	make -C ./libft

clean:
	rm -rf obj
	make -C ./libft/ clean

fclean: clean
	make -C ./libft/ fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re	
