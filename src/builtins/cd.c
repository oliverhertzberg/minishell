#include "../../headers/minishell.h"

void	ft_cd(t_cmd_data *cmd, t_hmap **env)
{
	char	*oldpwd;
	t_hmap	*temp;

	temp = *env;
	oldpwd = getcwd(NULL, 0);
	if (!get_value_hmap(env, "OLDPWD"))
		add_new_var(env, "OLDPWD", oldpwd);
	else
	{
		temp = get_value_hmap(env, "OLDPWD");
		temp->value = oldpwd;
	}
	change_dir(env, cmd);
	temp = get_value_hmap(env, "PWD");
	if (!temp)
	{
		add_new_var(env, "PWD", getcwd(NULL, 0));
		return ;
	}
	free(temp->value);
	temp->value = getcwd(NULL, 0);
	if (!temp->value)
		error_exit(NULL, "cd: error retrieving current directory: \
			getcwd: cannot access parent directories: No such file \
				or directory\n", &cmd, 1);
}
