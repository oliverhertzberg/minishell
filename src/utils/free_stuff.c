#include "../../headers/minishell.h"

void	free_hmap(t_hmap **v) //fix it
{
	t_hmap	*node;
	t_hmap	*temp;

	node = *v;
	while (node->next)
	{
		temp = node;
		node = node->next;
		if (temp == NULL)
			return ;
		if (temp->key != NULL)
		{
			free(temp->key);
			// temp->key = NULL;
		}
		if (temp->value != NULL)
		{
			free(temp->value);
			// temp->value = NULL;
		}
		free(temp);
	}
}

void	free_node(t_hmap *node)
{
	if (node == NULL)
		return ;
	if (node->key != NULL)
		free(node->key);
	if (node->value != NULL)
		free(node->value);
	free(node);
}

/* free double array */
void	ft_free(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
	s = NULL;
}

void	ft_free_key_value(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}
