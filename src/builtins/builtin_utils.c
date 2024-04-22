#include "../../headers/minishell.h"

int	already_in_list(char *key, t_env *env)
{
	int		i;
	char	*str;

	i = 0;
	str = key;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	while (env)
	{
		if (ft_strncmp(env->name, key, i) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}