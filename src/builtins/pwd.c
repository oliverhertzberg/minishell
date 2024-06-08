#include "../../headers/builtins.h"

void	ft_pwd(t_cmd_env *c)
{
	char	*pwd;

	if (get_value_hmap(c->hashmap, "PWD"))
		pwd = (get_value_hmap(c->hashmap, "PWD"))->value;
	else
		pwd = c->pwd;
	if (!pwd)
		exit(EXIT_FAILURE);
	printf("%s\n", pwd);
}
/*
void	ft_pwd(t_cmd_env *c)
{
	char	*pwd;

	pwd = c->pwd;
	if (!pwd)
		exit(EXIT_FAILURE);
	else
		printf("%s\n", pwd);
}*/
