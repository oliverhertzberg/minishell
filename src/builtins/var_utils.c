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
	{
		n++;
		i++;
	}
	key = malloc(n + 1);
	i = i - n;
	n = 0;
	while (input[i] != '=')
	{
		key[n] = input[i];
		n++;
		i++;
	}
	key[n] = '\0';
	return (key);
}

/* similar, just take value (what is after =) */
char	*take_value(char *input)
{
	int		start;
	int		end;
	int		i;
	char	*val;

	start = 0;
	while (input[start] != '=' && input[start] != '\0')
		start++;
	if ((input[start] == '\0') || (ft_isspace(input[start - 1]) == 1)
		|| (ft_isspace(input[start + 1]) == 1))
		return (NULL);
	start++;
	end = start;
	while (input[end] != '\0' && ft_isspace(input[end]) != 1)
		end++;
	val = malloc((end - start) + 1);
	if (!val) // add some error for allocation problems
		return (NULL);
	i = 0;
	while (start < end)
		val[i++] = input[start++];
	val[i] = '\0';
	return (val);
}

/* checking does key exists in list v, if it does, return 1,
 * if not 0. since u are comparing strings, use ft_strcmp  */
int	key_exists(t_var *v, char *key)
{
	while (v)
	{
		if (ft_strcmp(v->export_key, key) == 0)
			return (1);
		v = v->next;
	}
	return (0);
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
	t_var	*node;
	t_var	*temp;

	node = *v;
	while (node->next)
	{
		if (node->key == key)
		{
			temp = node->value;
			node->value = value;
			free(temp->value);
			break ;
		}
		node = node->next;
	}
}
