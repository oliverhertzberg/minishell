#include "../../headers/minishell.h"

void	free_hmap(t_hmap **v)
{
	t_hmap	*temp;

	if (!v)
		return ;
	while (*v)
	{
		temp = (*v)->next;
		if (temp == NULL)
			return ;
		ft_free_key_value((*v)->key, (*v)->value);
		free(*v);
		*v = temp;
	}
	*v = NULL;
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

void	free_all(t_cmd_data **d)
{
	free_hmap((*d)->env_ptr->hashmap);
	free_t_cmd_env((*d)->env_ptr);
	free_t_cmd_data(d, 1);
}
