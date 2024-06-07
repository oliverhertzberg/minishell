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
