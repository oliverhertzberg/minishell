#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_var t_var;

void	ft_strip(char **str);
int		is_substr(char *str, char *sub);
void	free_hmap(t_var **v);
void	ft_free(char **s);

#endif
