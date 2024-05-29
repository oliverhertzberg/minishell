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

/* if u find key inside of list v, free it's value and allocate new string with value that we are sending as an arg */
void	change_value(t_hmap **v, char *key, char *value)
{
	t_hmap	*node;

	node = *v;
	while (node->next)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			free(node->value);
			node->value = ft_strdup(value);
			if (!(node->value))
			{
				//error and free
				return ;
			}
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
