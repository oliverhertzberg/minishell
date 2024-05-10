#include "../../headers/minishell.h"

t_file	*file_lstnew(char *file, int fd, int append)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	new->file = file;
	new->fd = fd;
	new->append = append;
	new->next = NULL;
	return (new);
}

void    file_lstadd_back(t_file **lst, t_file *new)
{
	t_file	*node;

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

void	file_lstclear(t_file **lst)
{
	t_file	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->file);
		if ((*lst)->fd >= 0)
			close((*lst)->fd);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}


void	file_lstclear_last_fd_open(t_file **lst)
{
	t_file	*temp;
	if (!lst)
		return ;
	while ((*lst)->next)
	{
		temp = (*lst)->next;
		close((*lst)->fd);
		unlink((*lst)->file);
		free((*lst)->file);
		free(*lst);
		*lst = temp;
	}
	free ((*lst)->file);
	free (*lst);
	*lst = NULL;
}
