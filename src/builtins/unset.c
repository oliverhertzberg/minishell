#include "../../headers/builtins.h"

/* it needs to work for: unset  key. */
void	ft_unset(t_cmd_data *c, t_hmap **v)
{
	char	*key_to_unset;
	int		i;
	t_hmap	*node;

	i = 1;
	if (c->args[1] == NULL)
		return ;
	while (c->args[i])
	{
		key_to_unset = take_key(c->args[i]);
		if (ft_strcmp(key_to_unset, "PWD") == 0)
		{
			node = get_value_hmap(v, "PWD");
			node->show = 0;
			free (key_to_unset);
			return ;
		}
		if (key_exists(*v, key_to_unset) == 1)
			remove_var(v, key_to_unset);
		free(key_to_unset);
		i++;
	}
}
