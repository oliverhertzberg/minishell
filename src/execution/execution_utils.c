#include "../../headers/minishell.h"

t_cmd_data	*pop_node_in_use(t_cmd_data **lst)
{
	t_cmd_data	*current;
	t_cmd_data	*node_in_use;

	current = *lst;
	if (current->in_use == 1 || current->next == NULL)
	{
		*lst = current->next;
		current->next = NULL;
		return (current);
	}
	while (current)
	{
		if (current->next->in_use == 1)
		{
			node_in_use = current->next;
			current->next = current->next->next;
			node_in_use->next = NULL;
			return (node_in_use);
		}
		current = current->next;
	}
	return (NULL);
}

void	clear_pipes(t_cmd_env *e)
{
	int	i;

	if (!e->pipes)
		return ;
	i = 0;
	while (i < (e->num_of_cmds - 1) * 2)
	{
		if (e->pipes[i] >= 0)
			close(e->pipes[i]);
		i++;
	}
	free(e->pipes);
	e->pipes = NULL;
}

void	free_t_cmd_env(t_cmd_env *e)
{
	if (e->input != NULL)
	{
		free(e->input);
		e->input = NULL;
	}
	if (e->pipes != NULL)
		clear_pipes(e);
	if (e->pid != NULL)
	{
		free (e->pid);
		e->pid = NULL;
	}
	if (e->paths != NULL)
	{
		ft_free (e->paths);
		e->paths = NULL;
	}
	e->num_of_cmds = 1;
	e->parsing_error = 0;
}

void	free_t_cmd_data(t_cmd_data **d, int rm_hdoc)
{
	t_cmd_data	*temp;

	temp = *d;
	while (*d)
	{
		temp = (*d)->next;
		if ((*d)->heredoc != NULL)
			file_lstclear(&(*d)->heredoc, rm_hdoc);
		if ((*d)->infile != NULL)
			file_lstclear(&(*d)->infile, 0);
		if ((*d)->outfile != NULL)
			file_lstclear(&(*d)->outfile, 0);
		if ((*d)->cmd_path)
			free((*d)->cmd_path);
		if ((*d)->arg_lst)
			arg_lstclear(&(*d)->arg_lst);
		if ((*d)->args)
			ft_free((*d)->args);
		free ((*d));
		(*d) = temp;
	}
	d = NULL;
}
