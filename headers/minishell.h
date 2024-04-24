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
	int	single_quotes; // 1 if open, 0 if close
	int	double_quotes; // 1 if open, 0 if clone
}	t_parser;

typedef struct s_input
{
	t_var		*v;
	t_parser	*input_split;
}	t_input;


#endif
