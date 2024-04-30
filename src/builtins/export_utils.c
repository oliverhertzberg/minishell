#include "../../headers/builtins.h"

//use ft_strjoin
void	append_value(t_hmap **v, char *key, char *value)
{
	t_hmap	*node;
	char	*new_value;

	node = *v;
	new_value = (char *)malloc(ft_strlen(value) + 1);
	while (node->next)
	{
		if (node->key == key)
		{
			free(node->value);
			new_value = (char *)malloc(ft_strlen(value) + 1);
			if (!new_value)
			{
				free(node->value);
				return ;
			}
			node->value = new_value;
			break ;
		}
		node = node->next;
	}
}
