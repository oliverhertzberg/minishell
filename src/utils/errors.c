#include "../../headers/utils.h"

void	error_msg(char *c, char *str)
{
	write(2, "pipex: ", 7);
	if (c)
		write(2, c, ft_strlen(c));
	if (str)
		write(2, str, ft_strlen(str));
}

void	malloc_error(void)
{
	write(2, "pipex: alloaction failed\n", 26);
	exit(1);
}

void	quote_error(void)
{
	write(2, "pipex: quote error\n", 19);
	exit(1);
}
