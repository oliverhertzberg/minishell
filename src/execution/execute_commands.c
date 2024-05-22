#include "../../headers/minishell.h"

static	int	is_file(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strchr(cmd, '/') != NULL)
		return (1);
	return (0);
}

static char	*cmd_file_bin(char *cmd, char **paths, t_cmd_data **c)
{
	if (!paths && access(cmd, F_OK) != 0)
		error_exit(cmd, "No such file or directory\n", c, 127);
		// error_exit3(cmd, " No such file or directory\n", 127);
	if (access(cmd, F_OK) != 0)
	{
		if (is_file(cmd))
			error_exit(cmd, "No such file or directory\n", c, 127);
			//error_exit3(cmd, " No such file or directory\n", t, 127);
		else
			error_exit(cmd, " command not found\n", c, 127);
			// error_exit3(cmd, " command not found\n", t, 127);
	}
	if (is_file(cmd))
	{
		if (access(cmd, X_OK) != 0)
			error_exit(cmd, " Permission denied\n", c, 126);
			//error_exit3(cmd, " Permission denied\n", t, 126);
		else
			return (cmd);
	}
	error_exit(cmd, " command not found\n", c, 127);
	//error_exit3(cmd, " command not found\n", t, 127);
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **paths, t_cmd_data **c)
{
	char	*temp;
	char	*cmd_path;

	while (paths != NULL && *paths)
	{
		temp = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(temp, cmd);
		free (temp);
		if (!cmd_path)
			error_exit(cmd, " command not found\n", c, 127);
			// error_exit3(cmd, " command not found\n", 127);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (cmd_path);
			error_exit(cmd, " permission denied\n", c, 126);
			// error_exit3(cmd, " permission denied\n", 126);
		}
		free (cmd_path);
		paths++;
	}
	if (cmd_file_bin(cmd, paths, c) != NULL)
		return (cmd);
	error_exit(cmd, " No such file or directory\n", c, 127);
	// error_exit3(t->args[0], " No such file or directory\n", t, 127);
	return (NULL);
}

void	open_infiles(t_cmd_data **cmd)
{
	t_file	*last;

	last = NULL;
	while ((*cmd)->infile)
	{
		if (last)
		{
			close(last->fd);
			free(last->file);
			free(last);
		}
		last = (*cmd)->infile;
		(*cmd)->infile->fd = open((*cmd)->infile->file, O_RDONLY);
		if ((*cmd)->infile->fd < 0)
			error_exit((*cmd)->infile->file, NULL, cmd, 1);
		(*cmd)->infile = (*cmd)->infile->next;
	}
	(*cmd)->infile = last;
}

void	open_outfiles(t_cmd_data **cmd)
{
	t_file	*last;

	last = NULL;
	while ((*cmd)->outfile)
	{
		if (last)
		{
			close(last->fd);
			free(last->file);
			free(last);
		}
		last = (*cmd)->outfile;
		if ((*cmd)->outfile->append == 1)
		{
			if (((*cmd)->outfile->fd = open((*cmd)->outfile->file, O_APPEND \
				| O_CREAT | O_RDWR, 0644)) == -1)
				error_exit((*cmd)->outfile->file, NULL, cmd, 1);
		}
		else if ((*cmd)->outfile->append == 0)
		{
			if (((*cmd)->outfile->fd = open((*cmd)->outfile->file, O_TRUNC \
				| O_CREAT | O_RDWR, 0644)) == -1)
				error_exit((*cmd)->outfile->file, NULL, cmd, 1);
		}
		(*cmd)->outfile = (*cmd)->outfile->next;
	}
	(*cmd)->outfile = last;
}

void	clean_infiles(t_cmd_data **cmd)
{
	if ((*cmd)->heredoc)
	{
		close((*cmd)->heredoc->fd);
		free((*cmd)->heredoc->file);
		free((*cmd)->heredoc);
		(*cmd)->heredoc = NULL;
	}
	if ((*cmd)->infile)
	{
		close((*cmd)->infile->fd);
		free((*cmd)->infile->file);
		free((*cmd)->infile);
		(*cmd)->infile = NULL;
	}
}

void	clean_outfile(t_cmd_data **cmd)
{
	if ((*cmd)->outfile)
	{
		close((*cmd)->outfile->fd);
		free((*cmd)->outfile->file);
		free((*cmd)->outfile);
		(*cmd)->outfile = NULL;
	}
}

void	redirect_fd_in(t_cmd_data **cmd, t_cmd_env *e, int cmd_index)
{
	if ((*cmd)->is_here_doc == 1)
	{
		(*cmd)->heredoc->fd = open((*cmd)->heredoc->file, O_RDONLY);
		if ((*cmd)->heredoc->fd < 0)
			error_exit((*cmd)->heredoc->file, NULL, cmd, 1);
			//dprintf(2, "Failed to open heredoc\n");
		dup2((*cmd)->heredoc->fd, STDIN_FILENO); // check dup2
		clean_infiles(cmd); // can probably remove this and clear everything later with pipes
	}
	else if ((*cmd)->infile)
	{
		dup2((*cmd)->infile->fd, STDIN_FILENO); // check dup2
		clean_infiles(cmd); // this too
	}
	else if (cmd_index > 0)
		dup2(e->pipes[(cmd_index - 1) * 2], STDIN_FILENO); // check dup2
}

void	redirect_fd_out(t_cmd_data **cmd, t_cmd_env *e, int cmd_index)
{
	if ((*cmd)->outfile)
		dup2((*cmd)->outfile->fd, STDOUT_FILENO); // check dup2 return
	else if (cmd_index != (e->num_of_cmds - 1))
	{
		if (cmd_index == 0)
			dup2(e->pipes[1], STDOUT_FILENO); //dup2 fail
		else
			dup2(e->pipes[(cmd_index * 2) + 1], STDOUT_FILENO);
	}
}

void    execute_command(t_cmd_data **c, t_cmd_env *e, int cmd_index)
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
		exit(0);
	if (is_builtin(cmd_node))
		do_builtins(cmd_node, e);
	cmd_node->cmd_path = get_cmd_path(cmd_node->args[0], e->paths, &cmd_node);
	// dprintf(2, "cmd->path = %s\n", cmd_node->cmd_path);
	// int i;
	// i = -1;
	// while (cmd_node->args[++i])
	// 	dprintf(2, "cmd->args[%d] = %s\n", i, cmd_node->args[i]);
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

void	malloc_pid(t_cmd_env *e, t_cmd_data **c)
{
	e->pid = (pid_t *)malloc((e->num_of_cmds) * sizeof(pid_t));
	if (!e->pid)
		error_exit(NULL, "malloc failed\n", c, 1);
}

void	get_paths(t_cmd_env *e, t_cmd_data **c)
{
	char	*paths_string;

	paths_string = return_value_hash(*(e->hashmap), "PATH");
	if (paths_string == NULL)
		return ;
	e->paths = ft_split(paths_string, ':');
	if (!e->paths)
		error_exit(NULL, "malloc failed\n", c, 1);
}

void	handle_fork_failure(t_cmd_data **c, t_cmd_env *e, int child_count)
{
	int i;

	clear_pipes(e);
	i = -1;
	while (++i < child_count)
		waitpid(e->pid[i], NULL, 0);
	error_exit(NULL, "fork failed\n", c, 1);
}

void	execution(t_cmd_data **c, t_cmd_env *e)
{
	int			i;
	t_cmd_data	*current;

	malloc_and_create_pipes(e, c);
	if ((*c)->heredoc)
		close((*c)->heredoc->fd);
	if ((is_builtin(*c) == 1) && e->num_of_cmds == 1)
		do_builtins(*c, e);
	else
	{
		get_paths(e, c);
		malloc_pid(e, c);
		i = -1;
		current = *c;
		while (++i < e->num_of_cmds)
		{
			if ((e->pid[i] = fork()) < 0)
				handle_fork_failure(c, e, i);
			current->in_use = 1;
			if (e->pid[i] == 0)
				execute_command(c, e, i);
			current->in_use = 0;
			current = current->next;
		}
		clear_pipes(e);
		i = -1;
		while (++i < e->num_of_cmds)
		{
			//dprintf(2, "pid[i] == %d\n", e->pid[i]);
			waitpid(e->pid[i], &e->exit_code, 0);
		}
		free_t_cmd_data(c, 1);
		free_t_cmd_env(e);
        // only hashmap left in our env struct
	}
}
