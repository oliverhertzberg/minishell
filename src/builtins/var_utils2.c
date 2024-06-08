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
	if (!key)
		malloc_error();
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

static void	helping_funct(char *input, int *i, char **val)
{
	int		j;
	int		n;
	char	*temp;

	n = 0;
	while (input[++(*i)] != '\0')
		n++;
	temp = malloc(n + 1);
	if (!temp)
		malloc_error();
	*i = *i - n;
	j = 0;
	while (input[*i] != '\0')
	{
		temp[j] = input[*i];
		j++;
		(*i)++;
	}
	temp[j] = '\0';
	*val = ft_strdup(temp);
	free(temp);
}

/* similar, just take value (what is after =) */
char	*take_value(char *input)
{
	char	*val;
	int		i;

	i = 0;
	val = NULL;
	if (ft_strchr(input, '=') == NULL)
		return (NULL);
	while (input[i] != '\0')
	{
		if (input[i] == '=')
			break ;
		i++;
	}
	if (input[i + 1] == 0)
		return (NULL);
	helping_funct(input, &i, &val);
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
