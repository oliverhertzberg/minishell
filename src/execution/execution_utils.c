#include "../../headers/minishell.h"

t_cmd_data *pop_node_in_use(t_cmd_data **lst)
{
    t_cmd_data *current;
    t_cmd_data *node_in_use;

    current = *lst;
    if (current->in_use == 1)
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
        }
        current = current->next;
    }
}

void    clear_pipes(t_cmd_env *e)
{
    int i;

    i = 0;
    while (i < (e->num_of_cmds * 2))
    {
        if (e->pipes[i] == -2)
        {
            i++;
            continue ;
        }
        close(e->pipes[i++]);
    }
    free (e->pipes);
}

void    free_t_cmd_env(t_cmd_env *e)
{
    if (e->pipes != NULL)
        clear_pipes(e->pipes);
    if (e->pid != NULL)
        free (e->pid);
    if (e->paths != NULL)
        free (e->paths);
}

void	free_t_cmd_data(t_cmd_data **d)
{
	t_cmd_data	*temp;
	
	temp = *d;
	while (*d)
	{
        temp = (*d)->next;
		if ((*d)->heredoc != NULL)
			file_lstclear(&(*d)->heredoc);
		if ((*d)->infile != NULL)
			file_lstclear(&(*d)->infile);
		if ((*d)->outfile != NULL)
			file_lstclear(&(*d)->outfile);
        free ((*d));
		(*d) = temp;
	}
}

void    cleanup_resources_child(t_cmd_data *data, t_cmd_env *env)
{
    free_t_cmd_data(data);
    free_t_cmd_env(env);
}

