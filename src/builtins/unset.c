#include "../../headers/builtins.h"

static void	unset_error(char *input)
{
	ft_putstr_fd("Minishell: unset: '", 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

/* it needs to work for: unset  key.
 * u need to skip unset and all white spaces after it, and save key
 * into some string. then check if u have that key in v, and if u do
 * just remove it using function remove_var, if not do nothing */
void	ft_unset(char *input, t_hmap **v)
{
	char *key_to_unset;

	if (!input)
		return ;
	key_to_unset = take_key(input, 0);
	if (key_exists(key_to_unset) == 1)
		remove_var(v, key_to_unset);
	else
		unset_error(input);
}
