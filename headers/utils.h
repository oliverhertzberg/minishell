#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_var t_var;

/* white_spaces.c */
void	ft_strip(char **str);

/* free_stuff.c */
void	free_hmap(t_hmap **v);
void	ft_free(char **s);

/* errors.c */
void	error_msg(char *c, char *str);
void	malloc_error(void);
void	quote_error(void);

/* strings.c */
int		is_substr(char *str, char *sub);
char	*ft_strncpy(char *dest, char *src, int n);

/* quotes_handling.c */
int  check_word(char *string, int start, int end);

#endif
