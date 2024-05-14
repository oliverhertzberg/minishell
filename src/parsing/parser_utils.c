#include "../../headers/minishell.h"

// creates new command node and initializes values
t_cmd_data	*lstnew(void)
{
	t_cmd_data	*new;

	new = (t_cmd_data *)malloc(sizeof(t_cmd_data));
	if (!new)
		return (NULL);
	new->in_use = 0;
	new->is_here_doc = 0;
	new->fd_in = -2;
	new->fd_out = -2;
	new->heredoc = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->cmd_path = NULL;
	new->arg_lst = NULL;
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
		if ((*lst)->heredoc)
			file_lstclear((*lst)->heredoc);
		if ((*lst)->infile)
			file_lstclear((*lst)->infile);
		if ((*lst)->outfile)
			file_lstclear((*lst)->outfile);
		if ((*lst)->cmd_path)
			free ((*lst)->cmd_path);
		if ((*lst)->args)
			ft_free((*lst)->args);
		(*lst)->next = NULL;
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

