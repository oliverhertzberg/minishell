#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h> // readline
# include <readline/history.h> // add_history
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free, exit

# include "builtins.h"
# include "utils.h"
# include "../libft/libft.h"

typedef struct s_input
{
	t_var	*v;
	char	*input;
	char	**input_split;
}	t_input;


#endif
