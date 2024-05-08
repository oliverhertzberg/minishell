#include "../../headers/utils.h"

// create universal function that will free everything allocated, whatever exists, and add it every time 
// we have some error!!!
void	error_msg(char *c, char *str)
{
	write(2, "minishell: ", 12);
	if (c)
		write(2, c, ft_strlen(c));
	if (str)
		write(2, str, ft_strlen(str));
}

void	malloc_error(void)
{
	write(2, "minishell: alloaction failed\n", 30);
	exit(1);
}

void	quote_error(void)
{
	write(2, "minishell: quote error\n", 24);
	exit(1);
}
