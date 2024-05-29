#include "../../headers/minishell.h"

char	*get_cmd_path(char *cmd, char **paths, t_cmd_data **c)
{
	char	*temp;
	char	*cmd_path;

	while (paths != NULL && *paths)
	{
		temp = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(temp, cmd);
		if (!temp || !cmd_path)
			error_exit(NULL, "malloc failed\n", c, 1);
		free (temp);
		if (!cmd_path)
			error_exit(cmd, "command not found\n", c, 127);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (cmd_path);
			error_exit(cmd, "permission denied\n", c, 126);
		}
		free (cmd_path);
		paths++;
	}
	if (cmd_file_bin(cmd, paths, c) != NULL)
		return (cmd);
	error_exit(cmd, "No such file or directory\n", c, 127);
	return (NULL);
}

static	int	is_file(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strchr(cmd, '/') != NULL)
		return (1);
	return (0);
}

char	*cmd_file_bin(char *cmd, char **paths, t_cmd_data **c)
{
	if (!paths && access(cmd, F_OK) != 0)
		error_exit(cmd, "No such file or directory\n", c, 127);
	if (access(cmd, F_OK) != 0)
	{
		if (is_file(cmd))
			error_exit(cmd, "No such file or directory\n", c, 127);
		else
			error_exit(cmd, "command not found\n", c, 127);
	}
	if (is_file(cmd))
	{
		if (access(cmd, X_OK) != 0)
			error_exit(cmd, "Permission denied\n", c, 126);
		else
			return (cmd);
	}
	error_exit(cmd, "command not found\n", c, 127);
	return (NULL);
}
