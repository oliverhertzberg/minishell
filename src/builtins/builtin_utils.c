#include "../../headers/minishell.h"

int	already_in_list(char *name, t_hmap *env)
{
	int		i;
	char	*str;

	i = 0;
	str = name;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	while (env)
	{
		if (ft_strncmp(env->key, name, i) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	change_dir(t_hmap **env, t_cmd_data *cmd)
{
	t_hmap	*temp;
	char	*path;

	temp = *env;
	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "~"))
	{
		temp = get_value_hmap(env, "HOME");
		if (!temp)
			ft_puterror(1, "HOME not set\n", cmd);
		else if (chdir(temp->value) == -1)
			ft_puterror(1, "can't move to HOME directory\n", cmd);
	}
	else
	{
		path = take_path(cmd->args[1]);
		if (is_a_directory(path) && !does_not_exist(path))
		{
			if (!chdir(path))
				return ;
		}
		else if (!is_a_directory(path) && !does_not_exist(path))
			cd_error(cmd, " : Not a directory\n");
		else if (does_not_exist(path))
			cd_error(cmd, " : No such file or directory\n");
		free(path);
	}
}
