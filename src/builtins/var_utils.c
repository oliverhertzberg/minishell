#include "../../headers/builtins.h"

/* u get something like: export key="bla" and u need to take key, or 
 * and return it, and while doing it, u need to memorize where your
 iterator i is, so that we can follow where exactly are we in string input */
char	*take_key(char *input, int *i)
{
	char	*key;
	int		n;

	while (input[*i] != 0 && ft_isspace(input[*i]) == 1)
		(*i)++;
	n = 0;
	while (input[*i] != 0 && input[*i] != '=')
	{
		n++;
		(*i)++;
	}
	key = malloc(n + 1);
	if (!key) // error
		return (NULL);
	*i = *i - n;
	n = 0;
	while (input[*i] != '=' && input[*i] != 0)
	{
		key[n] = input[*i];
		n++;
		(*i)++;
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
		|| (ft_isspace(input[*i + 1]) == 1)) // check if any of these are printing errors
		return (NULL);
	if (input[*i] != '=') // error
		return (NULL);
	n = 0;
	while (input[++(*i)] != '\0' && ft_isspace(input[*i]) != 1)
		n++;
	val = malloc(n + 1);
	if (!val)  // add some error for allocation problems
		return (NULL);
	*i = *i - n;
	while (input[*i] != '\0' && ft_isspace(input[*i]) != 1)
	{
		val[n] = input[*i];
		n++;
		(*i)++;
	}
	val[n] = '\0';
	return (val);
}

/* checking does key exists in list v, if it does, return 1,
 * if not 0. since u are comparing strings, use ft_strcmp  */
int	key_exists(t_hmap *v, char *ekey)
{
	while (v)
	{
		if (ft_strcmp(v->key, ekey) == 0)
			return (1);
		v = v->next;
	}
	return (0);
}

/* returning value if key exists or NULL if not */
char	*return_value_hash(t_hmap *v, char *key)
{
	if (key_exists(v, key) == 1)
	{
		while (v->next)
		{
			if (v->key == key)
				return (v->value);
			v = v->next;
		}
	}
	return (NULL);
}

/* creating new node */
static t_hmap	*hmap_new(char *akey, char *avalue)
{
	t_hmap *node;

	if (!akey)
		return (NULL);
	node = (t_hmap *)malloc(sizeof(t_hmap));
	if (!node)
	{
		ft_putstr_fd("Memory allocation failed.\n", 2);
		exit(EXIT_FAILURE);
	}
	node->key = akey; //(*node).key
	if (!avalue)
		node->value = "";
	else
		node->value = avalue;
	node->next = NULL;
	return (node);
}

/* like adding at the back of the list node with key and value */
void	add_new_var(t_hmap **v, char *akey, char *avalue)
{
	t_hmap *node;
	t_hmap *temp;

	node = hmap_new(akey, avalue);
	if (!node)
		return ;
	if (*v == NULL)
	{
		*v = node;
	}
	else
	{
		temp = *v;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

/* remove node from list v, that has concrete key in it */
void	remove_var(t_hmap **v, char *rkey)
{
	t_hmap	*node;
	t_hmap	*temp;

	node = *v;
	if (node->key == rkey)
	{
		temp = node;
		node = node->next;
		free_hmap(&temp);
		return;
	}
	while (node->next)
	{
		if (node->next->key == rkey)
		{
			temp = node->next;
			node = node->next->next;
			free_hmap(&temp);
			break ;
		}
		node = node->next;
	}
}

/* if u find key inside of list v, free it's value and allocate new string with value that we are sending as an arg */
void	change_value(t_hmap **v, char *key, char *value)
{
	t_hmap	*node;
	// char	*new_value;

	node = *v;
	// new_value = (char *)malloc(ft_strlen(value) + 1);
	while (node->next)
	{
		if (node->key == key)
		{
			free(node->value);
			node->value = (char *)malloc(ft_strlen(value) + 1);
			if (!node->value)
			{
				free(node->value);
				return ;
			}
			node->value = value;
			break ;
		}
		node = node->next;
	}
}
