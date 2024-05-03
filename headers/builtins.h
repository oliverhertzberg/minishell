#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>

# include "utils.h"
# include "../libft/libft.h"

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
	char	*value; // everything after name with skipping spaces between them
	t_hmap	*h; // check should we sent it a separate arg or include it here
}	t_builtins;

/* exit.c */
void ft_exit(t_hmap **env, char *input);

/* pwd.c */
char	*ft_pwd(void);

/* cd.c */
void ft_cd(char *input, t_hmap **env);

/* env.c */
t_hmap	*init_hmap(char **env);
void	ft_env(t_hmap **hashmap, int is_env);

/* echo.c */
void	ft_echo(t_builtins *b);

/* echo_utils.c */
void	print_space(t_builtins *b, int i);
void	print_string(t_builtins *b, int start, int end);
void	handle_dolar(t_builtins *b, int start, int end);
void	handle_mix(t_builtins *b, int start, int end);

/* export.c */
void	ft_export(char *input, t_builtins *b, int *i, t_hmap **hsmap);

/* export_utils.c */
void	append_value(t_hmap **v, char *key, char *value);
void	check_append(t_hmap **hmap, char *key, char *value);

/* unset.c */
void		ft_unset(char *input, t_hmap **v);

/* builtins.c */
void  		do_builtins(char *line, int *i, t_builtins *b);
t_builtins  create_builtins(char **line);

/* builtin_utils.c */
void	update_dir(char *case, char *value, t_hmap **env);
int		already_in_list(char *name, t_hmap *env);

/* var_utils.c */ //split into 2 files!!!
char	*take_key(char *input, char *i);
char	*take_value(char *input, int *i);
int		key_exists(t_hmap *v, char *ekey);
char	*return_value_hash(t_hmap *v, char *key);
void	add_new_var(t_hmap **v, char *akey, char *avalue);
void	remove_var(t_hmap **v, char *rkey);
void	change_value(t_hmap **v, char *key, char *value);

#endif
