#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include "../libft/libft.h"
# include "minishell.h"
# include "builtins.h"

typedef struct s_hmap t_hmap;
typedef struct s_cmd_data t_cmd_data;

/* white_spaces.c */
void	ft_strip(char **str);

/* free_stuff.c */
void	free_hmap(t_hmap **v);
void	free_node(t_hmap *node);
void	ft_free(char **s);
void	ft_free_key_value(char *key,char *value);

/* errors.c */
void	error_msg(char *c, char *str);
void	malloc_error(void);
void	quote_error(void);
void 	ft_puterror(int code, char *str, t_cmd_data *cmd);

/* strings.c */
int     is_substr(char *str, char *sub);
void	ft_strncpy(char *dest, char *src, int n);
int     ft_atoi_short(char *str);
void    ft_skip_fl(char **str);

/* quotes_handling.c */
int     check_word(char *string, int start, int end);
int     is_inside_quotes(char *str, int start, int end);
int   inside_mix(char *str, int start, int end);

#endif
