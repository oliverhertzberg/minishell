#include "../../headers/minishell.h"

/*
typedef struct s_cmd_env
{
	int 	*pipes;
	int		num_of_cmds;
	char	**paths;
	int 	exit_code;
	t_hmap **hashmap;
}	t_cmd_env;
*/
/*
typedef struct	s_cmd_data
{
	int		is_here_doc;
	t_file	*heredoc;
	t_file	*infile;
	t_file	*outfile;
	int		append;
	int		fd_in;
	int		fd_out;
	char	*cmd_path;
	char 	**args;
	struct s_cmd_data *next;
}	t_cmd_data;
*/
// cat Makefile >>test.c | wc
// free whole cmd_data struct

static char	*cmd_file_bin(char *cmd, char **paths)
{
	if (!paths && access(cmd, F_OK) != 0)
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

void    

void    execute_command(t_cmd_data **c_data, t_cmd_env *c_env)
{
    t_cmd_data *cmd;

    cmd = pop_node_in_use(c_data);
    lstclear(c_data);
    get_fd_in(cmd);
    get_fd_out(cmd);
    redirect_stdinout(cmd);
    cmd->cmd_path = get_cmd_path(cmd->args[0], c_env->paths);
    close_pipes(cmd)
    free_c_env();
}

void    malloc_and_create_pipes(t_cmd_env *c_env)
{
    int i;

    if (c_env->num_of_cmds == 1)
        return ;
    c_env->pipes = (int *)malloc(((c_env->num_of_cmds - 1) * 2) * sizeof(int));
    // malloc error
    i = 0;
    while (i < ((c_env->num_of_cmds - 1) * 2))
    {
        if (pipe(c_env->pipes[i]) == -1)
            // pipe error
        i += 2;
    }

}

void    malloc_pid(t_cmd_env *c_env)
{
    c_env->pid = (pid_t *)malloc((c_env->num_of_cmds) * sizeof(pid_t));
    // malloc error
}

void    execution(t_cmd_data **c, t_cmd_env *c_env)
{
    int i;
    t_cmd_data *current;

    malloc_and_create_pipes(c_env);
    malloc_pid(c_env);
    i = -1;
    current = *c;
    while (++i < c_env->num_of_cmds)
    {
        c_env->pid[i] = fork();
        // fork error
        current->in_use = 1;
        if (c_env->pid[i] == 0)
            execute_command(c, c_env);
        current->in_use = 0;
        current = current->next;
    }
    free_t_cmd_data(c);
    // also include closing pipes and freeing memory in c_env in free_t_cmd_data
    i = -1;
    while (++i < c_env->num_of_cmds)
        waitpid(c_env->pid[i], &c_env->exit_code, 0);
}
