#include "../../headers/builtins.h"
/* u get something like: export key="bla" and u need to take key, or 
 * however it was named there and return it */
char	*take_key(char *input)
{
	char	*key;
	int		i;
	int		n;

	i = 6;
	while (input[i] != 0 && ft_isspace(input[i]) == 1)
		i++;
	n = 0;
	while (input[i] != 0 && input[i] != '=')
		n++;
	key = malloc(n + 1);

}

/* similar, just take value (what is after =) */
char	*take_value(char *input)
{

}

/* checking does key exists in list v, if it does, return 1,
 * if not 0. since u are comparing strings, use ft_strcmp  */
int	key_exists(t_var *v, char *key)
{

}

/* like adding at the back of the list node with key and value */
void	add_new_var(t_var **v, char *key, char *value)
{
	t_var *node;
	t_var *temp;

	if (!key || !value)
		return ;
	node->key = key; //(*node).key
	node->value = value;
	node->next = NULL;
	if (*v == NULL)
		*v = node;
	else
	{
		temp = *v;
		while (temp->next)
			temp = temp->next;
		temp->next = *node;
	}
}

/* remove node from list v, that has concrete key in it */
void	remove_var(t_var **v, char *key)
{
	t_var	*node;
	t_var	*temp;

	node = *v;
	while (node->next)
	{
		if (node->next->key == key)
		{
			temp = node->next;
			node = node->next->next;
			free(temp->key);
			free(temp->value);
			temp->next = NULL //might not be needed
			break ;
		}
		node = node->next;
	}
}

/* if u find key inside of list v, free it's value and allocate new string with value that we are sending as an arg */
void	change_value(t_var **v, char *key, char *value)
{

}
