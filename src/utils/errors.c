#include "../../headers/minishell.h"

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

// error_exit3(cmd, " No such file or directory\n", 127);
void	malloc_error(void)
{
	write(2, "minishell: memoryallocation failed\n", 30);
	exit(1);
}

void	quote_error(void) //remove this and include it in code
{
	write(2, "minishell: quote error\n", 24);
	exit(1);
}

void	error_exit(char *error, t_cmd_data **d, t_cmd_env *e)
{
	if (error != 0)
		perror(error);
	free_t_cmd_data(d);
	free_t_cmd_env(e);
	exit(e->exit_code);
}

// exit code can be found in t_cmd_env struct exit code, need to set it 
// before calling exit function
void	error_exit_msg(char *c, char *str, t_cmd_data **d, t_cmd_env *e)
{
	error_msg(c, str);
	error_exit(0, d, e);
}

void	ft_puterror(int code, char *str, t_cmd_data *cmd)
{
	char	*msg;
	char	*temp;

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
	ft_putendl_fd(msg, 2);
	free(msg);
	exit(code); //will need to change the exit_code later
}
