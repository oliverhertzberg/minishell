#include "../../headers/builtins.h"

/* returning value if key exists or NULL if not */
char	*return_value_hash(t_hmap *v, char *key)
{
	if (key_exists(v, key) == 1)
	{
		while (v)
		{
			if (ft_strcmp(v->key, key) == 0)
				return (v->value);
			v = v->next;
		}
	}
	return (NULL);
}

void	change_value(t_hmap **v, char *key, char *value)
{
	t_hmap	*node;

	if (!v || !(*v) || !key)
		return ;
	node = *v;
	while (node->next)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			free(node->value);
			node->value = ft_strdup(value);
			if (!(node->value))
				malloc_error();
			break ;
		}
		node = node->next;
	}
}

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
