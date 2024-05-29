#include "../../headers/builtins.h"

/* remove node from list v, that has concrete key in it */
void	remove_var(t_hmap **v, char *rkey)
{
	t_hmap	*node;
	t_hmap	*temp;

	if (v == NULL || *v == NULL || rkey == NULL)
		return ;
	node = *v;
	if (ft_strcmp(node->key, rkey) == 0)
	{
		temp = node;
		*v = node->next;
		free_node(temp);
		return ;
	}
	while (node->next)
	{
		if (ft_strcmp(node->next->key, rkey) == 0)
		{
			temp = node->next;
			node->next = node->next->next;
			free_node(temp);
			break ;
		}
		node = node->next;
	}
}

/* u get something like: export key="bla" and u need to take key, or 
 * and return it, and while doing it, u need to memorize where your
 iterator i is, so that we can follow where exactly are we in string input */
char	*take_key(char *input)
{
	char	*key;
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (input[i] != 0 && input[i] != '=')
	{
		n++;
		i++;
	}
	key = malloc(n + 1);
	if (!key) // error
		return (NULL);
	i = i - n;
	n = 0;
	while (input[i] != '=' && input[i] != 0)
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
	int		n;
	char	*val;
	int		i;

	i = 0;
	if (ft_strchr(input, '=') == NULL)
		return (NULL);
	while (input[i] != '\0')
	{
		if (input[i] == '=')
			break ;
		i++;
	}
	n = 0;
	if (input[i + 1] == 0)
		return (NULL);
	while (input[++i] != '\0')
		n++;
	val = malloc(n + 1);
	if (!val)  // add some error for allocation problems
		return (NULL);
	i = i - n;
	n = 0;
	while (input[i] != '\0')
	{
		val[n] = input[i];
		n++;
		i++;
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