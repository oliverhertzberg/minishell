#include "../../headers/minishell.h"

int	already_in_list(char *name, t_env *env)
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

void	update_dir(char *case, char *value, t_hmap **env)
{
	t_hmap	*str;

	str = *env;
	if (!ft_strcmp(case, "opwd"))
	{
		while (ft_strncmp("OLDPWD", str->key, 6))
			str = str->next;
		free(str->value);
		str->value = ft_strdup(value);
	}
	else if (case == 'pwd')
	{
		while (ft_strncmp("PWD", str->key, 3))
			str = str->next;
		free(str->value);
		str->value = ft_strdup(value);
	}
}
