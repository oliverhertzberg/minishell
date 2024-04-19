#include "../../headers/builtins.h"

/* u get something like: export key="bla" and u need to take key, or 
 * and return it, and while doing it, u need to memorize where your
 iterator i is, so that we can follow where exactly are we in string input */
char	*take_key(char *input, char *i)
{
	char	*key;
	int		n;

	while (input[*i] != 0 && ft_isspace(input[*i]) == 1)
		*i++;
	n = 0;
	while (input[*i] != 0 && input[*i] != '=')
	{
		n++;
		*i++;
	}
	key = malloc(n + 1);
	if (!key)
		// error
		return (NULL);
	*i = *i - n;
	n = 0;
	while (input[*i] != '=' && input[*i] != 0)
	{
		key[n] = input[*i];
		n++;
		*i++;
	}
	key[n] = '\0';
	return (key);
}

/* similar, just take value (what is after =) */
char	*take_value(char *input, int *i)
{
	int		n;
	char	*val;

	if ((input[*i] == '\0') || (ft_isspace(input[*i - 1]) == 1)
		|| (ft_isspace(input[*i + 1]) == 1))
		return (NULL);
	if (input[*i] != '=') // error
		return (NULL);
	*i++;
	n = 0;
	while (input[*i] != '\0' && ft_isspace(input[*i]) != 1)
	{
		*i++;
		n++;
	}
	val = malloc(n + 1);
	if (!val)  		// add some error for allocation problems
		return (NULL);
	*i = *i - n;
	while (input[*i] != '\0' && ft_isspace(input[*i]) != 1)
	{
		val[n] = input[*i];
		n++;
		*i++;
	}
	val[n] = '\0';
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
	node->export_key = key; //(*node).key
	node->export_value = value;
	node->next = NULL;
	if (*v == NULL)
		*v = node;
	else
	{
		temp = *v;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

/* remove node from list v, that has concrete key in it */
void	remove_var(t_var **v, char *key)
{
	t_var	*node;
	t_var	*temp;

	node = *v;
	if (node->export_key == key)
	{
		temp = node;
		node = node->next;
		free_t_var(temp);
		return;
	}
	while (node->next)
	{
		if (node->next->export_key == key)
		{
			temp = node->next;
			node = node->next->next;
			free_t_var(temp);
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
		if (node->export_key == key)
		{
			temp->export_value = node->export_value;
			node->export_value = value;
			free(temp->export_value);
			break ;
		}
		node = node->next;
	}
}
