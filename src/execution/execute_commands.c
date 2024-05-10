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
/*
void    execute_command(t_cmd_data **c_data, t_cmd_data *c, t_cmd_env *c_env)
{
    get_fd_in(c);
    get_fd_out(c);
    redirect_stdinout(c);
    close_pipes()
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
        if (c_env->pid[i] == 0)
            execute_command(c, current, c_env);
        current = current->next;
    }
    free_t_cmd_data(c);
    // also include closing pipes and freeing memory in c_env in free_t_cmd_data
    i = -1;
    while (++i < c_env->num_of_cmds)
        waitpid(c_env->pid[i], &c_env->exit_code, 0);
}*/
