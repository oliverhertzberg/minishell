#include "../../headers/minishell.h"

void free_t_var(t_var *temp)
{
    if (temp == NULL)
        return; // If temp is already NULL, no need to free anything
    // Free the export_key
    if (temp->export_key != NULL)
	{
        free(temp->export_key);
        temp->export_key = NULL; // Optional
    }
    // Free the export_value member
    if (temp->export_value != NULL)
	{
        free(temp->export_value);
        temp->export_value = NULL; // Optional
    }
    free(temp);
}

void	free_hsmap(t_var **v)
{
	t_var	*node;
	t_var	*temp;

	node = *v;
	while (node->next)
	{
		temp = node;
		node = node->next;
		free_t_var(temp);
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
