#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>

# include "utils.h"
# include "../libft/libft.h"

typedef struct s_var
{
	char	*export_var;
	char	*export_string;
}	t_var;

void	ft_pwd(void);
void	ft_echo(char *input)

#endif
