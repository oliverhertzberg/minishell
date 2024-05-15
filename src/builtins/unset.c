#include "../../headers/builtins.h"

/* it needs to work for: unset  key.
 * u need to skip unset and all white spaces after it, and save key
 * into some string. then check if u have that key in v, and if u do
 * just remove it using function remove_var, if not do nothing */
void	ft_unset(char *input, t_hmap **v)
{
	char *key_to_unset;

	if (!input)
		return ;
	key_to_unset = take_key(input);
	if (key_exists(*v, key_to_unset) == 1)
		remove_var(v, key_to_unset);
}
