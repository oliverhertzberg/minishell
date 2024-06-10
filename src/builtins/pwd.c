#include "../../headers/builtins.h"

void	ft_pwd(t_hmap **hmap)
{
	char	*pwd;

	pwd = (get_value_hmap(hmap, "PWD"))->value;
	if (!pwd)
		exit(EXIT_FAILURE);
	else
		printf("%s\n", pwd);
}
