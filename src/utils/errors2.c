#include "../../headers/minishell.h"

void	parsing_error(char *msg, int *parseerror, t_cmd_data **d, int exit_code)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (parseerror)
		*parseerror = 1;
	(*d)->env_ptr->exit_code = exit_code;
}

void	cd_error(char *cmd, char *str)
{
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(str, 2);
}

void	ft_puterror2(int code, char *str, t_cmd_data **cmd)
{
	char	*msg;
	char	*temp;

	if ((code == 127 || code == 126) && cmd)
	{
		temp = ft_strdup((*cmd)->args[0]);
		if (!temp)
			exit(1);
		msg = ft_strjoin(temp, str);
		free(temp);
	}
	else
		msg = ft_strdup(str);
	if (!msg)
		exit(1);
	ft_putendl_fd(msg, 2);
	free(msg);
	(*cmd)->env_ptr->exit_code = 1;
}
