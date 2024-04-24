#include "../../headers/minishell.h"

t_parser	*lstnew(char *content)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	new->string = content;
	new->next = NULL;
	return (new);
}

void    lstadd_back(t_parser **lst, t_parser *new)
{
	t_parser	*node;

	if (!new)
		return ;
	else if (*lst == NULL)
		*lst = new;
	else
	{
		node = *lst;
		while (node->next)
			node = node->next;
		node->next = new;
	}
}

void	lstclear(t_parser **lst)
{
	t_parser	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->string);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}