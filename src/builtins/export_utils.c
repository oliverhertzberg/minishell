#include "../../headers/minishell.h"

// void	append_value(t_hmap **v, char *key, char *value)
// {
// 	t_hmap	*node;
// 	char	*old_value;

// 	node = *v;
// 	while (node->next)
// 	{
// 		if (node->key == key)
// 		{
// 			old_value = (char *)malloc(ft_strlen(node->value) + 1);
// 			old_value = node->value;
// 			free(node->value);
// 			node->value = (char *)malloc(ft_strlen(value) + ft_strlen(old_value) + 1);
// 			if (!node->value)
// 			{
// 				free(node->value);
// 				return ;
// 			}
// 			node->value = ft_strjoin(old_value, value);
// 			break ;
// 		}
// 		node = node->next;
// 	}
// }
