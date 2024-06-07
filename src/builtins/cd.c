#include "../../headers/minishell.h"

static void	print_err_and_set_exitcode(t_cmd_data **d)
{
	(*d)->env_ptr->exit_code = 1;
	psfd("cd: error retrieving current directory: ", 2);
	psfd("getcwd: cannot access parent directories: ", 2);
	psfd("No such file or directory\n", 2);
}

static void	check_cd_path(t_cmd_data **d, t_hmap **env)
{
	t_hmap	*temp;

	if (!(*d)->args[1]
		|| (!ft_strcmp((*d)->args[1], ".") || !ft_strcmp((*d)->args[1], "..")
			|| !ft_strcmp((*d)->args[1], "/")))
	{
		print_err_and_set_exitcode(d);
		return ;
	}
	else if (!does_not_exist((*d)->args[1]))
	{
		if (!is_a_directory((*d)->args[1]))
		{
			cd_error((*d)->args[1], " : Not a directory\n");
			return ;
		}
		temp = get_value_hmap(env, "PWD");
		free (temp->value);
		temp->value = ft_strdup((*d)->args[1]);
		if (!temp->value)
			exit(1);
		chdir(temp->value);
		return ;
	}
	print_err_and_set_exitcode(d);
}

void	ft_cd(t_cmd_data **cmd, t_hmap **env)
{
	char	*oldpwd;
	t_hmap	*temp;

	temp = *env;
	if (does_not_exist((get_value_hmap(env, "PWD"))->value))
		return (check_cd_path(cmd, env));
	oldpwd = getcwd(NULL, 0);
	if (!get_value_hmap(env, "OLDPWD"))
		add_new_var(env, "OLDPWD", oldpwd);
	else
	{
		temp = get_value_hmap(env, "OLDPWD");
		temp->value = oldpwd;
	}
	change_dir(env, *cmd);
	temp = get_value_hmap(env, "PWD");
	if (!temp)
	{
		add_new_var(env, "PWD", getcwd(NULL, 0));
		return ;
	}
	free(temp->value);
	temp->value = getcwd(NULL, 0);
}
