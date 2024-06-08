#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include "../libft/headers/libft.h"
# include "minishell.h"
# include "builtins.h"

typedef struct s_hmap		t_hmap;
typedef struct s_cmd_data	t_cmd_data;

/* white_spaces.c */
void	ft_strip(char **str);

/* free_stuff.c */
void	free_hmap(t_hmap **v);
void	free_node(t_hmap *node);
void	ft_free(char **s);
void	ft_free_key_value(char *key, char *value);
void	free_all(t_cmd_data **d);

/* errors.c */
void	error_msg(char *c, char *str);
void	malloc_error(void);
void	quote_error(void);
void	ft_puterror(int code, char *str, t_cmd_data *cmd);
void	ft_puterror2(int code, char *str, t_cmd_data **cmd);
void	error_exit(char *item, char *msg, t_cmd_data **d, int exit_code);

/* errors2.c*/
void	cd_error(char *cmd, char *str);
void	parsing_error(char *msg, int *parse_error,
			t_cmd_data **d, int exit_code);

#endif
