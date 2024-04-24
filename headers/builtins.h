#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>

# include "utils.h"
# include "../libft/libft.h"

# define HASHMAP_SIZE 100

/* hashmap struct */
typedef struct s_hmap
{
	char			*key;
	char			*value;
	struct s_hmap	*next;
}	t_hmap;

typedef struct s_builtins
{
	char	*name; //name of builtins that we are using
	t_var	*v;
}	t_builtins;

int		key_exists(t_var *v, char *key);
char	*take_key(char *input, char *i);
char	*take_value(char *input, int *i);
void	add_new_var(t_var **v, char *key, char *value);
void	remove_var(t_var **v, char *key);
void	change_value(t_var **v, char *key, char *value);
void	ft_env(t_env *env);
void	ft_exit(char *input);
void	ft_cd(char *input, t_env **env);
char	*ft_pwd(void);
void	ft_echo(char *input);

#endif
