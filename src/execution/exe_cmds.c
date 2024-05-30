#include "../../headers/minishell.h"

static void	malloc_pid(t_cmd_env *e, t_cmd_data **c)
{
	e->pid = (pid_t *)malloc((e->num_of_cmds) * sizeof(pid_t));
	if (!e->pid)
		error_exit(NULL, "malloc failed\n", c, 1);
}

static void	get_paths(t_cmd_env *e, t_cmd_data **c)
{
	char	*paths_string;

	paths_string = return_value_hash(*(e->hashmap), "PATH");
	if (paths_string == NULL)
		return ;
	e->paths = ft_split(paths_string, ':');
	if (!e->paths)
		error_exit(NULL, "malloc failed\n", c, 1);
}

static void	handle_fork_failure(t_cmd_data **c, t_cmd_env *e, int child_count)
{
	int	i;

	clear_pipes(e);
	i = -1;
	while (++i < child_count)
		waitpid(e->pid[i], NULL, 0);
	error_exit(NULL, "fork failed\n", c, 1);
}

static void	fork_and_exec(t_cmd_data **c, t_cmd_env *e)
{
	int			i;
	t_cmd_data	*current;

	current = *c;
	i = -1;
	while (++i < e->num_of_cmds)
	{
		e->pid[i] = fork();
		if (e->pid[i] < 0)
			handle_fork_failure(c, e, i);
		current->in_use = 1;
		if (e->pid[i] == 0)
		{
			//set_signals_from_child();
			execute_command(c, e, i);
		}
		current->in_use = 0;
		current = current->next;
	}
}

void	execution(t_cmd_data **c, t_cmd_env *e)
{
	int			i;

	malloc_and_create_pipes(e, c);
	get_paths(e, c);
	if ((is_builtin(*c) == 1) && e->num_of_cmds == 1)
		do_builtins(c);
	else
	{
		malloc_pid(e, c);
		fork_and_exec(c, e);
		clear_pipes(e);
		i = -1;
		while (++i < e->num_of_cmds)
		{
			//set_signals_from_parent();
			// set_signals_from_child();
			waitpid(e->pid[i], &e->exit_code, 0);
			e->exit_code = WEXITSTATUS(e->exit_code);
		}
		free_t_cmd_data(c, 1);
		free_t_cmd_env(e);
	}
}
