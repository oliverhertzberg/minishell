#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>

# include "utils.h"
# include "../libft/headers/libft.h"

typedef struct s_cmd_data	t_cmd_data;
typedef struct s_cmd_env	t_cmd_env;

/* hashmap struct */
typedef struct s_hmap
{
	char			*key;
	char			*value;
	struct s_hmap	*next;
}	t_hmap;

/* exit.c */
void	ft_exit(t_cmd_data **p, t_cmd_env *e);
void	rl_clear_history(void);

/* pwd.c */
void	ft_pwd(t_cmd_env *c);

/* cd.c */
void	ft_cd(t_cmd_data **cmd, t_hmap **env);
void	change_dir(t_hmap **env, t_cmd_data **cmd);
int		does_not_exist(char *path);
int		is_a_directory(char *path);
void	helping_function2(t_hmap **env, t_cmd_data **cmd);

/* env.c */
t_hmap	**init_hmap(char **env);
void	ft_env(t_hmap *hashmap, int is_env);
int		hashmap_size(t_hmap *hashmap);
char	**env_to_str(t_hmap *hashmap);

/* echo.c */
void	ft_echo(t_cmd_data *d);

/* echo_utils.c */
void	print_space(t_cmd_data *d, int i);
void	print_string(t_cmd_data *d, int i, int start, int end);

/* export.c */
void	ft_export(t_cmd_data *c, t_hmap **hsmap);

/* unset.c */
void	ft_unset(t_cmd_data *c, t_hmap **v);

/* builtins.c */
void	do_builtins(t_cmd_data **d);

//int		check_builtins(t_cmd_data **d);
int		is_builtin(t_cmd_data *data);

/* builtin_utils.c */
void	update_dir(char *c, char *value, t_hmap **env);
int		already_in_list(char *name, t_hmap *env);

/* var_utils.c */
char	*take_key(char *input);
char	*take_value(char *input);
int		key_exists(t_hmap *v, char *ekey);
char	*return_value_hash(t_hmap *v, char *key);
void	add_new_var(t_hmap **v, char *akey, char *avalue);
void	add_new_var1(t_hmap **v, char *akey);
void	remove_var(t_hmap **v, char *rkey);
void	change_value(t_hmap **v, char *key, char *value);
t_hmap	*get_value_hmap(t_hmap **head, char *key);

/* shellevel.c */
void	add_shelllevel(t_hmap	**hashmap);

#endif
