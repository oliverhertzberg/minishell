#include "../../headers/builtins.h"

void	ft_pwd(t_cmd_env *c)
{
	char	*pwd;

	pwd = (get_value_hmap(c->hashmap, "PWD"))->value;
	if (!pwd)
		pwd = c->pwd;
	if (!pwd)
		exit(EXIT_FAILURE);
	printf("%s\n", pwd);
}

void	ft_pwd(t_cmd_env *c)
{
	char	*pwd;

	pwd = c->pwd;
	if (!pwd)
		exit(EXIT_FAILURE);
	else
		printf("%s\n", pwd);
}