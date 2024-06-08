#include "../../headers/minishell.h"

int	does_not_exist(char *path)
{
	int	is_accessible;

	is_accessible = access(path, F_OK);
	if (is_accessible < 0)
		return (1);
	return (0);
}

int	is_a_directory(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static char	*take_path(char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (cmd[i] != '\0' && cmd[i] != ' ')
		i++;
	path = ft_substr(cmd, 0, i);
	return (path);
}

void	helping_function2(t_hmap **env, t_cmd_data **cmd)
{
	t_hmap	*temp;

	temp = get_value_hmap(env, "HOME");
	if (!temp)
		ft_puterror2(1, "HOME not set", cmd);
	else if (chdir(temp->value) == -1)
		ft_puterror2(1, "can't move to HOME directory", cmd);
}

void	change_dir(t_hmap **env, t_cmd_data **cmd)
{
	t_hmap	*temp;
	char	*path;

	temp = *env;
	if (!(*cmd)->args[1] || !ft_strcmp((*cmd)->args[1], "~"))
		helping_function2(env, cmd);
	else
	{
		path = take_path((*cmd)->args[1]);
		if (is_a_directory(path) && !does_not_exist(path))
			chdir(path);
		else if (!is_a_directory(path) && !does_not_exist(path))
		{
			cd_error((*cmd)->args[1], " : Not a directory\n");
			(*cmd)->env_ptr->exit_code = 1;
		}
		else if (does_not_exist(path))
		{
			cd_error((*cmd)->args[1], " : No such file or directory\n");
			(*cmd)->env_ptr->exit_code = 1;
		}
		free(path);
	}
}
