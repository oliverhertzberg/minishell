#include "../../headers/minishell.h"

t_cmd_data	*lstnew(void)
{
	t_cmd_data	*new;

	new = (t_cmd_data *)malloc(sizeof(t_cmd_data));
	if (!new)
		return (NULL);
	new->is_here_doc = 0;
	new->fd_in = -2;
	new->fd_out = -2;
	new->append = 0;
	new->heredoc = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->cmd_path = NULL;
	new->args = NULL;
	new->next = NULL;
	return (new);
}

void    lstadd_back(t_cmd_data **lst, t_cmd_data *new)
{
	t_cmd_data	*node;

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

void	lstclear(t_cmd_data **lst)
{
	t_cmd_data	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	free_t_cmd_data(t_cmd_data **p)
{
	t_cmd_data	*node;
	
	node = *p;
	while (node->next)
	{
		if (node->heredoc != NULL)
			file_lstclear(&node->heredoc);
		if (node->infile != NULL)
			file_lstclear(&node->infile);
		if (node->outfile != NULL)
			file_lstclear(&node->outfile);
		if (node->cmd_path != NULL)
			free(node->cmd_path);
		if (node->args != NULL)
			ft_free(node->args);
		node = node->next;
	}
}
