#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>

# include "utils.h"
# include "../libft/libft.h"

# define HASHMAP_SIZE 100 //change it

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
	t_hmap	*v;
}	t_builtins;

int		key_exists(t_hmap *v, char *key);
char	*take_key(char *input, char *i);
char	*take_value(char *input, int *i);
void	add_new_var(t_hmap **v, char *key, char *value);
void	remove_var(t_hmap **v, char *key);
void	change_value(t_hmap **v, char *key, char *value);
void	ft_env(t_hmap **hashmap, int is_env)
void 	ft_exit(t_stack env, char *input)
void	ft_cd(char *input, t_hmap **env);
char	*ft_pwd(void);
void	ft_echo(char *input);
t_hmap	*init_hmap(char **env);

#endif
