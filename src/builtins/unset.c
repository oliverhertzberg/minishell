#include "../../headers/builtins.h"

/* it needs to work for: unset  key. */
void	ft_unset(t_cmd_data *c, t_hmap **v)
{
	char *key_to_unset;

	// if (!c->args[1])
	// 	return ;
	// if (ft_strchr(c->args[1], '=') != NULL)
	// {
	// 	ft_putstr_fd("Minishell: unset: \'", 2);
	// 	ft_putstr_fd(c->args[1], 2);
	// 	ft_putstr_fd("\': not a valid idenftifier\n", 2);
	// 	return ;
	// }
	key_to_unset = take_key(c->args[1]);
	if (key_exists(v, key_to_unset) == 1)
		remove_var(&v, key_to_unset);
}
