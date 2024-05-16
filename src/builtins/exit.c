#include "../../headers/minishell.h"

static int is_valid(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_msg_exit(t_cmd_data *p, int code)
{
	ft_putendl_fd("exit", 2);
	clear_history();
	free_t_cmd_data(&p);
	exit(code);
}

static int overflow(char *str)
{
	long int code;

	code = 0;
	while (*str)
	{
		if ((code > LONG_MAX / 10) && ((code = LONG_MAX / 10) \
			|| ((*str - '0') > LONG_MAX % 10)))
			return (1);
		code = (code * 10) + ((*str) - '0');
		str++;
	}
	return (0);
}

void ft_exit(t_cmd_data **p, char *status) //fix this!
{
	int code;

	if (status == NULL)
		ft_msg_exit(*p, 0);
	if (!is_valid(status) || overflow(status))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(status, 2);
		ft_putendl_fd(": numeric argument required", 2);
		free_t_cmd_data(p);
		exit(255);
	}
	if ((*p)->args[2] != NULL)
		return (ft_putendl_fd("minishell: exit: too many arguments", 2));
	code = ft_atoi(status);
	ft_msg_exit(*p, code);
}
