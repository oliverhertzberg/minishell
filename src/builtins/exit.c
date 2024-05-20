#include "../../headers/minishell.h"

static int is_valid(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
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

static long long overflow(char *str)
{
	long long code;

	code = 0;
	while (*str)
	{
		if (code > LONG_MAX / 10 || (code == LONG_MAX / 10 && *str > '7'))
			return (1);
		code = (code * 10) + ((*str) - '0');
		str++;
	}
	return (0);
}

static long long	ft_atoi_exit(const char *str)
{
	long long		nr;
	int				i;
	int				sgn;

	nr = 0;
	i = 0;
	sgn = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sgn = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nr > LONG_MAX / 10 || (nr == LONG_MAX / 10 && str[i] > '7'))
		{
			if (sgn == 1)
				return (-1);
			else
				return (0);
		}
		nr = nr * 10 + (str[i] - '0');
		i++;
	}
	return (nr * sgn);
}

void ft_exit(t_cmd_data **p, t_cmd_env e) //fix this!
{
	int code;

	code = e.exit_code;
	if ((*p)->args[1] != NULL)
	{
		if ((*p)->args[2] != NULL)
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			exit(1);
		}
		code = ft_atoi_exit((*p)->args[1]);
		if (is_valid((*p)->args[1]) == 0 || overflow((*p)->args[1]))
		{
			printf("1\n");
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd((*p)->args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			free_t_cmd_data(p);
			printf("2\n");
			exit(255);
		}
	}
	printf("3\n");
	ft_msg_exit(*p, code);
}
