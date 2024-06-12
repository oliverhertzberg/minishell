#include "../../headers/builtins.h"

static void	new_line_flag(int flag)
{
	if (flag == 0)
		write(1, "\n", 1);
}

static void	skip_nl(int *k, t_cmd_data *d, int *f)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 1;
	while (d->args[i] != 0 && ft_strncmp(d->args[i], "-n", 2) == 0)
	{
		j = 2;
		while (d->args[i][j] == 'n')
			j++;
		if (d->args[i][j] == 0)
			flag = 1;
		else
			break ;
		i++;
	}
	*k = i;
	*f = flag;
}

void	ft_echo(t_cmd_data *d)
{
	int	i;
	int	flag;

	skip_nl(&i, d, &flag);
	while (d->args[i])
	{
		ft_putstr_fd(d->args[i], 1);
		if (d->args[i + 1] != 0)
			write(1, " ", 1);
		i++;
		if (d->args[i] == 0 && i != d->arg_count)
		{
			write(1, " ", 1);
			i++;
		}
	}
	new_line_flag(flag);
}
