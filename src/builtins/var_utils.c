#include "../../headers/builtins.h"

/* returning node that has key */
t_hmap	*get_value_hmap(t_hmap **head, char *key)
{
	t_hmap	*temp;

	temp = *head;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/* creating new node (when we have =) */
static t_hmap	*hmap_new(char *akey, char *avalue)
{
	t_hmap	*node;

	if (!akey)
		return (NULL);
	node = (t_hmap *)malloc(sizeof(t_hmap));
	if (!node)
	{
		ft_putstr_fd("Memory allocation failed.\n", 2);
		exit(EXIT_FAILURE);
	}
	node->show = 1;
	node->key = ft_strdup(akey);
	if (!avalue)
		node->value = ft_strdup("");
	else
		node->value = ft_strdup(avalue);
	node->next = NULL;
	return (node);
}

/* no = */
static t_hmap	*hmap_new1(char *akey)
{
	t_hmap	*node;

	if (!akey)
		return (NULL);
	node = (t_hmap *)malloc(sizeof(t_hmap));
	if (!node)
	{
		ft_putstr_fd("Memory allocation failed.\n", 2);
		exit(EXIT_FAILURE);
	}
	node->key = ft_strdup(akey);
	node->value = NULL;
	node->next = NULL;
	return (node);
}

/* adding at the back of the list node with key and value (= is included) */
void	add_new_var(t_hmap **v, char *akey, char *avalue)
{
	t_hmap	*node;
	t_hmap	*temp;

	if (akey[0] == ' ')
		node = hmap_new(akey + 1, NULL);
	else
		node = hmap_new(akey, avalue);
	if (!node)
		return ;
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

/* no = */
void	add_new_var1(t_hmap **v, char *akey)
{
	t_hmap	*node;
	t_hmap	*temp;

	node = hmap_new1(akey);
	if (!node)
		return ;
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
