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
	write(2, "minishell: allocation failed\n", 30);
	exit(1);
}

void	quote_error(void)
{
	write(2, "minishell: quote error\n", 24);
	exit(1);
}

void ft_puterror(int code, char *str, t_cmd_data *cmd)
{
	char *msg;
	char *temp;

	if ((code == 127 || code == 126) && cmd)
	{
		temp = ft_strdup(cmd->args[0]);
		if (!temp)
			malloc_error();
		msg = ft_strjoin(temp, str);
		free(temp);
	}
	else
		msg = ft_strdup(str);
	if (!msg)
		malloc_error();
	ft_putendl_fd(msg, 2, 1);
	free(msg);
	
}