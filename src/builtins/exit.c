#include "../../headers/minishell.h"

// check for overflows long max, min
void ft_exit(t_hmap **hmap, t_parser **p, int code)
{
	int i;

	code = 0;
	i = 0;
	if ((*p)->args[0] != NULL)
	{
		while ((*p)->args[0][i])
		{
			if (ft_isdigit((*p)->args[0][i]) == 0)
			{
				ft_putstr_fd("minishell: exit:", 2);
				ft_putstr_fd((*p)->args[0], 2);
				ft_putstr_fd(":  numeric argument required", 2);
				code = 255;
				break ;
			}
			i++;
			code = ft_atoi((*p)->args[0]);

		}
	}
	ft_putstr_fd("\n", 1);
	// rl_clear_history();
	free_hmap(hmap);
	exit(code);
}
