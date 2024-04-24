#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h> // readline
# include <readline/history.h> // add_history
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free, exit, getenv

# include "builtins.h"
# include "utils.h"
# include "../libft/libft.h"

typedef struct	s_parser
{
	char	*string;
	struct s_parser *next;
}	t_parser;

typedef struct s_input
{
	t_var		*v;
	t_parser	*input_split;
}	t_input;

t_parser	*lstnew(char *content);
void    lstadd_back(t_parser **lst, t_parser *new);
void	lstclear(t_parser **lst);

#endif
