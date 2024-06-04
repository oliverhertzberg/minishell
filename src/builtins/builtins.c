#include "../../headers/builtins.h"

static void	dup_stdio(t_cmd_data **d)
{
	(*d)->env_ptr->stdin_cpy = dup(STDIN_FILENO);
	if ((*d)->env_ptr->stdin_cpy == -1)
		error_exit(NULL, NULL, d, 1);
	(*d)->env_ptr->stdout_cpy = dup(STDOUT_FILENO);
	if ((*d)->env_ptr->stdout_cpy == -1)
		error_exit(NULL, NULL, d, 1);
}

void	do_builtins(t_cmd_data **d)
{
	if ((*d)->env_ptr->num_of_cmds == 1)
	{
		dup_stdio(d);
		if (!open_infiles(d) || !open_outfiles(d)
			|| !redirect_fd_out(d, (*d)->env_ptr, 0)
			|| !redirect_fd_in(d, (*d)->env_ptr, 0))
			return ;
	}
	if (ft_strcmp((*d)->args[0], "cd") == 0)
		ft_cd(*d, (*d)->env_ptr->hashmap);
	if (ft_strcmp((*d)->args[0], "echo") == 0)
		ft_echo(*d);
	if (ft_strcmp((*d)->args[0], "pwd") == 0)
		ft_pwd();
	if (ft_strcmp((*d)->args[0], "export") == 0)
		ft_export(*d, (*d)->env_ptr->hashmap);
	if (ft_strcmp((*d)->args[0], "unset") == 0)
		ft_unset(*d, (*d)->env_ptr->hashmap);
	if (ft_strcmp((*d)->args[0], "env") == 0)
		ft_env(*((*d)->env_ptr->hashmap), 1);
	if (ft_strcmp((*d)->args[0], "exit") == 0)
		ft_exit(d, (*d)->env_ptr);
	free_t_cmd_env((*d)->env_ptr);
	free_t_cmd_data(d, 1);
}

int	is_builtin(t_cmd_data *data)
{
	if (!data->args || !data->args[0])
		return (0);
	if (check_word(data->args[0], 0, ft_strlen(data->args[0])) == 2)
		ft_skip(data->args[0]);
	if (check_word(data->args[0], 0, ft_strlen(data->args[0])) == 3)
	{
		if (ft_strcmp(data->args[0], "echo") == 0
			|| ft_strcmp(data->args[0], "cd") == 0
			|| ft_strcmp(data->args[0], "pwd") == 0
			|| ft_strcmp(data->args[0], "export") == 0
			|| ft_strcmp(data->args[0], "unset") == 0
			|| ft_strcmp(data->args[0], "env") == 0
			|| ft_strcmp(data->args[0], "exit") == 0)
			return (1);
	}
	return (0);
}
