#include "../../headers/minishell.h"

int	redirect_fd_in(t_cmd_data **cmd, t_cmd_env *e, int cmd_index)
{
	if ((*cmd)->is_here_doc == 1)
	{
		(*cmd)->heredoc->fd = open((*cmd)->heredoc->file, O_RDONLY);
		if ((*cmd)->heredoc->fd < 0)
			return (error_exit((*cmd)->heredoc->file,
					"failed to open here_doc\n", cmd, 1), 0);
		if (dup2((*cmd)->heredoc->fd, STDIN_FILENO) == -1)
			return (error_exit(NULL, NULL, cmd, 1), 0);
		clean_infiles(cmd);
	}
	else if ((*cmd)->infile)
	{
		if (dup2((*cmd)->infile->fd, STDIN_FILENO) == -1)
			return (error_exit(NULL, NULL, cmd, 1), 0);
		clean_infiles(cmd);
	}
	else if (cmd_index > 0)
		if (dup2(e->pipes[(cmd_index - 1) * 2], STDIN_FILENO) == -1)
			return (error_exit(NULL, NULL, cmd, 1), 0);
	return (1);
}

int	redirect_fd_out(t_cmd_data **cmd, t_cmd_env *e, int cmd_index)
{
	if ((*cmd)->outfile)
	{
		if (dup2((*cmd)->outfile->fd, STDOUT_FILENO) == -1)
			return (error_exit(NULL, NULL, cmd, 1), 0);
	}
	else if (cmd_index != (e->num_of_cmds - 1))
	{
		if (cmd_index == 0)
		{
			if (dup2(e->pipes[1], STDOUT_FILENO) == -1)
				return (error_exit(NULL, NULL, cmd, 1), 0);
		}
		else
		{
			if (dup2(e->pipes[(cmd_index * 2) + 1], STDOUT_FILENO) == -1)
				return (error_exit(NULL, NULL, cmd, 1), 0);
		}
	}
	return (1);
}

void	execute_command(t_cmd_data **c, t_cmd_env *e, int cmd_index)
{
	t_cmd_data	*cmd_node;

	cmd_node = pop_node_in_use(c);
	lstclear(c);
	open_infiles(&cmd_node);
	open_outfiles(&cmd_node);
	redirect_fd_out(&cmd_node, e, cmd_index);
	redirect_fd_in(&cmd_node, e, cmd_index);
	clear_pipes(e);
	if (!cmd_node->args || !cmd_node->args[0])
	{
		free_t_cmd_data(&cmd_node, 1);
		free_t_cmd_env(e);
		exit(0);
	}
	if (is_builtin(cmd_node))
		do_builtins(cmd_node, e);
	cmd_node->cmd_path = get_cmd_path(cmd_node->args[0], e->paths, &cmd_node);
	execve(cmd_node->cmd_path, cmd_node->args, e->env_copy);
	error_exit(NULL, "execve failed\n", &cmd_node, 1);
}

void	malloc_and_create_pipes(t_cmd_env *e, t_cmd_data **c)
{
	int	i;
	int	j;

	if (e->num_of_cmds == 1)
		return ;
	e->pipes = (int *)malloc(((e->num_of_cmds - 1) * 2) * sizeof(int));
	if (!e->pipes)
		error_exit(NULL, "malloc failed\n", c, 1);
	i = 0;
	while (i < (e->num_of_cmds - 1))
	{
		if (pipe(e->pipes + 2 * i) < 0)
		{
			j = 0;
			while (j < i * 2)
				close(e->pipes[j++]);
			free(e->pipes);
			e->pipes = NULL;
			error_exit(NULL, "failed to create pipes\n", c, 1);
		}
		i++;
	}
}
