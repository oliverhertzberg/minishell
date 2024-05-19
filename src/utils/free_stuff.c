#include "../../headers/minishell.h"

void	free_hmap(t_hmap **v)
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
    	    temp->key = NULL; // Optional
    	}
    	if (temp->value != NULL)
		{
	        free(temp->value);
    	    temp->value = NULL; // Optional
    	}
    	free(temp);
	}
}

void	free_node(t_hmap *node)
{
	t_hmap *temp;

	if (node == NULL)
		return ;
	temp = node;
	temp = temp->next;
    if (node->key != NULL)
	{
        free(node->key);
        node->key = NULL; // Optional
    }
    if (node->value != NULL)
	{
		free(node->value);
		node->value = NULL; // Optional
    }
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
void	ft_free_key_value(char *key,char *value)
{
	if (!key)
		return ;
	if (!value)
		return ;
	free(key);
	free(value);
}