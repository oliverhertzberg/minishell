#include "../../headers/minishell.h"

static	int	is_file(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strchr(cmd, '/') != NULL)
		return (1);
	return (0);
}

static char	*cmd_file_bin(char *cmd, char **paths)
{
	if (!paths && access(cmd, F_OK) != 0)
        exit(1);
		// error_exit3(cmd, " No such file or directory\n", 127);
	if (access(cmd, F_OK) != 0)
	{
		if (is_file(cmd))
            exit(1);
			//error_exit3(cmd, " No such file or directory\n", t, 127);
		else
            exit (1);
			// error_exit3(cmd, " command not found\n", t, 127);
	}
	if (is_file(cmd))
	{
		if (access(cmd, X_OK) != 0)
            exit(1);
			//error_exit3(cmd, " Permission denied\n", t, 126);
		else
			return (cmd);
	}
	//error_exit3(cmd, " command not found\n", t, 127);
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **paths)
{
	char	*temp;
	char	*cmd_path;

	while (paths != NULL && *paths)
	{
		temp = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(temp, cmd);
		free (temp);
		if (!cmd_path)
            exit(1);
			// error_exit3(cmd, " command not found\n", 127);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (cmd_path);
			// error_exit3(cmd, " permission denied\n", 126);
		}
		free (cmd_path);
		paths++;
	}
	if (cmd_file_bin(cmd, paths) != NULL)
		return (cmd);
	// error_exit3(t->args[0], " No such file or directory\n", t, 127);
	return (NULL);
}

void	open_infiles(t_cmd_data **cmd)
{
    t_file *last;

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
	    {
		    ft_putstr_fd("minishell: ", 2);
		    ft_putstr_fd((*cmd)->infile->file, 2);
		    ft_putstr_fd(": ", 2);
		    perror("");
	    }
        (*cmd)->infile = (*cmd)->infile->next;
    }
    (*cmd)->infile = last;
}

void    open_outfiles(t_cmd_data **cmd)
{
    t_file *last;

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
            if (((*cmd)->outfile->fd = open((*cmd)->outfile->file, O_APPEND | O_CREAT | O_RDWR, 0644)) == -1)
                exit(1);
        }
        else if ((*cmd)->outfile->append == 0)
        {
            if (((*cmd)->outfile->fd = open((*cmd)->outfile->file, O_TRUNC | O_CREAT | O_RDWR, 0644)) == -1)
                exit(1);
        }
        (*cmd)->outfile = (*cmd)->outfile->next;
    }
    (*cmd)->outfile = last;
}

void    clean_infiles(t_cmd_data **cmd)
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

void    clean_outfile(t_cmd_data **cmd)
{
    if ((*cmd)->outfile)
    {
        close((*cmd)->outfile->fd);
        free((*cmd)->outfile->file);
        free((*cmd)->outfile);
        (*cmd)->outfile = NULL;
    }
}

void    redirect_fd_in(t_cmd_data **cmd, t_cmd_env *e, int cmd_index)
{
    if ((*cmd)->is_here_doc == 1)
    {
        (*cmd)->heredoc->fd = open((*cmd)->heredoc->file, O_RDONLY);
        if ((*cmd)->heredoc->fd < 0)
            dprintf(2, "Failed to open heredoc\n");
        dup2((*cmd)->heredoc->fd, STDIN_FILENO); // check dup2
        dprintf(2, "here_doc->fd = %d\n",(*cmd)->heredoc->fd);
        clean_infiles(cmd); // can probably remove this and clear everything later with pipes
    }
    else if ((*cmd)->infile)
    {
        dprintf(2, "infile condition\n");
        dup2((*cmd)->infile->fd, STDIN_FILENO); // check dup2
        dprintf(2, "infile->fd = %d\n",(*cmd)->infile->fd);
        clean_infiles(cmd); // this too
    }
    else if (cmd_index > 0)
    {
        dup2(e->pipes[(cmd_index - 1) * 2], STDIN_FILENO); // check dup2
        dprintf(2, "fd_in = %d for cmd_index:%d\n", e->pipes[(cmd_index - 1) * 2], cmd_index);
    }
}

void    redirect_fd_out(t_cmd_data **cmd, t_cmd_env *e, int cmd_index)
{
    if ((*cmd)->outfile)
    {
        dup2((*cmd)->outfile->fd, STDOUT_FILENO); // check dup2 return
    }
    else if (cmd_index != (e->num_of_cmds - 1))
    {
        if (cmd_index == 0)
        {
            dup2(e->pipes[1], STDOUT_FILENO); //dup2 fail
            dprintf(2, "fd_out = %d for cmd_index: %d\n", e->pipes[1], cmd_index);
        }
        else
        {
            dup2(e->pipes[(cmd_index * 2) + 1], STDOUT_FILENO);
            dprintf(2, "fd_out = %d for cmd_index: %d\n", e->pipes[(cmd_index * 2) + 1], cmd_index);
        }
    }
}

void    execute_command(t_cmd_data **c_data, t_cmd_env *c_env, int cmd_index)
{
    t_cmd_data *cmd_node;

    cmd_node = pop_node_in_use(c_data);
    lstclear(c_data);
    open_infiles(&cmd_node);
    open_outfiles(&cmd_node);
    redirect_fd_out(&cmd_node, c_env, cmd_index);
    redirect_fd_in(&cmd_node, c_env, cmd_index);
    clear_pipes(c_env);
    cmd_node->cmd_path = get_cmd_path(cmd_node->args[0], c_env->paths);
    dprintf(2, "cmd->path = %s\n", cmd_node->cmd_path);
    int i = -1;
    while (cmd_node->args[++i])
        dprintf(2, "cmd->args[%d] = %s\n", i, cmd_node->args[i]);
    execve(cmd_node->cmd_path, cmd_node->args, c_env->env_copy);
    dprintf(2, "execve failed \n");
    exit(1);
}

void    malloc_and_create_pipes(t_cmd_env *c_env)
{
    int i;
    int j;

    if (c_env->num_of_cmds == 1)
        return ;
    dprintf(2, "num of cmds = %d\n", c_env->num_of_cmds);
    c_env->pipes = (int *)malloc(((c_env->num_of_cmds - 1) * 2) * sizeof(int));
    // malloc error
    i = 0;
    while (i < (c_env->num_of_cmds - 1))
	{
		if (pipe(c_env->pipes + 2 * i) < 0)
		{
			j = 0;
			while (j < i * 2)
				close(c_env->pipes[j++]);
			free(c_env->pipes);
            dprintf(2, "create pipes error\n");
            c_env->pipes = NULL;
            exit(1);
		}
		i++;
    }
}

void    malloc_pid(t_cmd_env *c_env)
{
    c_env->pid = (pid_t *)malloc((c_env->num_of_cmds) * sizeof(pid_t));
    // malloc error
}

void    get_paths(t_cmd_env *c_env)
{
    char *paths_string;

    paths_string = return_value_hash(*(c_env->hashmap), "PATH");
    if (paths_string == NULL)
        return ;
    c_env->paths = ft_split(paths_string, ':');
    // malloc error
}

//cat -e makefile | cat | wc
void    execution(t_cmd_data **c, t_cmd_env *c_env)
{
    int i;
    t_cmd_data *current;

    malloc_and_create_pipes(c_env);
    if ((*c)->heredoc)
        close((*c)->heredoc->fd);
    malloc_pid(c_env);
    get_paths(c_env);
    //dprintf(2, "%s\n", );
    i = -1;
    current = *c;
    while (++i < c_env->num_of_cmds)
    {
        c_env->pid[i] = fork();
        // fork error
        current->in_use = 1;
        if (c_env->pid[i] == 0)
            execute_command(c, c_env, i);
        current->in_use = 0;
        current = current->next;
    }
    clear_pipes(c_env);
    // also include closing pipes and freeing memory in c_env in free_t_cmd_data
    i = -1;
    while (++i < c_env->num_of_cmds)
    {
        dprintf(2, "pid[i] == %d\n", c_env->pid[i]);
        waitpid(c_env->pid[i], &c_env->exit_code, 0);
    }
    free_t_cmd_data(c);
}
