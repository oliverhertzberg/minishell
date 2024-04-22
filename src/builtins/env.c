#include "../../headers/minishell.h"
//We need to create hashmap with all the env variables and with this function we print it
int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value && env->value != '\0')
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
