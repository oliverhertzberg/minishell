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
    	    free(temp->export_key);
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

/* free double array */
void	ft_free(char **s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return ;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}
