#include "../../headers/builtins.h"

static void	unset_oldpwd(t_hmap **h)
{
	if (return_value_hash(*h, "OLDPWD"))
		remove_var(h, "OLDPWD");
}

void	add_shelllevel(t_hmap	**hashmap)
{
	t_hmap	*h_temp;
	int		shlvl;

	h_temp = get_value_hmap(hashmap, "SHLVL");
	shlvl = ft_atoi_short(h_temp->value);
	if (shlvl < 0)
		shlvl = 0;
	free(h_temp->value);
	h_temp->value = ft_itoa(shlvl + 1);
	unset_oldpwd(&h_temp);
}
