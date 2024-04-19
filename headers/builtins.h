#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>

# include "utils.h"
# include "../libft/libft.h"

void	ft_pwd(void);
void	ft_echo(char *input);

/* hashmap struct */
typedef struct s_var
{
	char			*export_key;
	char			*export_value;
	struct s_var	*next;
}	t_var;

typedef struct s_builtins
{
	char	*name; //name of builtins that we are using
	t_var	*v;
}	t_builtins;

int	key_exists(t_var *v, char *key);
char	*take_key(char *input, char *i);
char	*take_value(char *input);
void	add_new_var(t_var **v, char *key, char *value);
void	remove_var(t_var **v, char *key);
void	change_value(t_var **v, char *key, char *value);

#endif
