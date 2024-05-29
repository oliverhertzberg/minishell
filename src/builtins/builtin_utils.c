#include "../../headers/minishell.h"

int	already_in_list(char *name, t_hmap *env)
{
	int		i;
	char	*str;

	i = 0;
	str = name;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	while (env)
	{
		if (ft_strncmp(env->key, name, i) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
