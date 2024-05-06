#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include "../libft/libft.h"
# include "minishell.h"
# include "builtins.h"

typedef struct s_hmap t_hmap;

/* white_spaces.c */
void	ft_strip(char **str);

/* free_stuff.c */
void	free_hmap(t_hmap **v);
void	free_node(t_hmap *node);
/*void	ft_free(char **s);
void	ft_free_key_value(char *key,char *value);*/

/* errors.c */
/*void	error_msg(char *c, char *str);
void	malloc_error(void);
void	quote_error(void);*/

/* strings.c */
int	is_substr(char *str, char *sub);
char	*ft_strncpy(char *dest, char *src, int n);

/* quotes_handling.c */
/*int	check_word(char *string, int start, int end);
int	is_inside_quotes(char *str, int start, int end);*/

#endif
