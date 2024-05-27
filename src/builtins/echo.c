#include "../../headers/builtins.h"

void    ft_echo(t_cmd_data *d)
{
    int i;
    int flag;
    int	j;

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
    while (d->args[i] != 0)
    {
        ft_putstr_fd(d->args[i], 1);
        if (d->args[i + 1] != 0)
            write(1, " ", 1);
        i++;
    }
    if (flag == 0)
 		write(1, "\n", 1);
}
