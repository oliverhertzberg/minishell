#include "../../headers/minishell.h"

static void	print_err_and_set_exitcode(t_cmd_data **d)
{
	(*d)->env_ptr->exit_code = 1;
	psfd("cd: error retrieving current directory: ", 2);
	psfd("getcwd: cannot access parent directories: ", 2);
	psfd("No such file or directory\n", 2);
}

static void	change_to_home(t_cmd_data **d, t_hmap **env)
{
	t_hmap	*home;
	t_hmap	*temp;

	home = get_value_hmap(env, "HOME");
	if (!home)
		return (ft_puterror2(1, "HOME not set", d));
	else if (chdir(home->value) == -1)
		return (ft_puterror2(1, "can't move to HOME directory", d));
	temp = get_value_hmap(env, "PWD");
	free (temp->value);
	temp->value = ft_strdup(home->value);
	if (!temp->value)
		exit(1);
	free ((*d)->env_ptr->PWD);
	(*d)->env_ptr->PWD = ft_strdup(home->value);
	if (!(*d)->env_ptr->PWD)
		malloc_error();	
}

static void	check_cd_path(t_cmd_data **d, t_hmap **env)
{
	char	*temp;

	if (((*d)->args[1] && ((*d)->args[1][0] ==  '.'
			|| ((*d)->args[1][0] ==  '/'))))
		return (print_err_and_set_exitcode(d));
	else if (!(*d)->args[1])
	{
		change_to_home(d, env);	
		return ;
	}
	else if (!does_not_exist((*d)->args[1]))
	{
		if (!is_a_directory((*d)->args[1]))
			return (cd_error((*d)->args[1], " : Not a directory\n"));
		temp = (*d)->env_ptr->PWD;
		(*d)->env_ptr->PWD = ft_strdup((*d)->args[1]);
		if (!(*d)->env_ptr->PWD)
			exit(1);
		free (temp);
		chdir((*d)->env_ptr->PWD);
		return ;
	}
	print_err_and_set_exitcode(d);
}

static void	update_oldpwd(t_hmap **env, char *oldpwd)
{
	t_hmap	*temp;

	temp = get_value_hmap(env, "OLDPWD");
	free (temp->value);
	temp->value = oldpwd;
}

void	update_pwd_hashmap(char	*new_pwd, t_hmap **hmap)
{
	t_hmap	*pwd;

	pwd = get_value_hmap(hmap, "PWD");
	if (!pwd)
		return ;
	free (pwd->value);
	pwd->value = ft_strdup(new_pwd);
	if (!pwd->value)
		malloc_error();
}

void	ft_cd(t_cmd_data **cmd, t_hmap **env)
{
	char	*oldpwd;
	t_hmap	*temp;
	temp = *env;
	if (does_not_exist((*cmd)->env_ptr->PWD))
	{
		check_cd_path(cmd, env);
		update_pwd_hashmap((*cmd)->env_ptr->PWD, env);
		return ;
	}
	oldpwd = getcwd(NULL, 0);
	if (!get_value_hmap(env, "OLDPWD"))
	{
		add_new_var(env, "OLDPWD", oldpwd);
		free (oldpwd);
	}
	else
		update_oldpwd(env, oldpwd);
	change_dir(env, cmd);
	free ((*cmd)->env_ptr->PWD);
	(*cmd)->env_ptr->PWD = getcwd(NULL, 0);
	update_pwd_hashmap((*cmd)->env_ptr->PWD, env);
}
