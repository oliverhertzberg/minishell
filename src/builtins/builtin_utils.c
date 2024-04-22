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

void	update_dir(char *case, char *value, t_env **env)
{
	t_env	*str;

	str = *env;
	if (case == 'opwd')
	{
		while (ft_strncmp("OLDPWD", str->name, 6) != 0)
			str = str->next;
		free(str->value);
		str->value = ft_strdup(value);
	}
	else if (case == 'pwd')
	{
		while (ft_strncmp("PWD", str->name, 3) != 0)
			str = str->next;
		free(str->value);
		str->value = ft_strdup(value);
	}
}