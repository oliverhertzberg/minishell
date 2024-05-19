#include "../../headers/minishell.h"

t_arg_lst   *arg_lstnew(char *arg)
{
    t_arg_lst *new;

    new = (t_arg_lst *)malloc(sizeof(t_arg_lst));
    if (!new)
        exit (1);
        //malloc error
    new->arg = arg;
    new->next = NULL;
    return (new);
}
void    arg_lstadd_back(t_arg_lst **lst, t_arg_lst *new)
{
	t_arg_lst	*node;

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

void	arg_lstclear(t_arg_lst **lst)
{
	t_arg_lst	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	lst = NULL;
}

