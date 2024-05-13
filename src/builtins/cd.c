#include "../../headers/minishell.h"

//access(const char *pathname, int mode): checks whether the calling process has the specified mode of access permissions to the file or directory specified by pathname.
//If the file or directory does not exist or the calling process lacks the necessary permissions, access() returns -1
//F_OK: to check if the file exists

//chdir((char *path)) returning 0 on success and -1 on failure
//input = av[1]
//getenv retrieves the value of the environment variable named name.
// static int does_not_exist(char *path)
// {
// 	int is_accessible;

// 	is_accessible = access(path, F_OK);
// 	if (is_accessible < 0)
// 		return (1);
// 	return (0);
// }
// static int is_a_directory(char *path)
// {
// 	int fd;

// 	fd = open(path, O_DIRECTORY);
// 	if (fd < 0)
// 		return (0);
// 	close(fd);
// 	return (1);
// }

static char *take_path(char *cmd)
{
	char    *path;
    int		i;

    i = 0;
    while (cmd[i] != '\0' && cmd[i] != ' ')
        i++;
    path = ft_substr(cmd, 0, i);
    return (path);
}

static void    cd_error(t_cmd_data *cmd, char *str)
{
    ft_putstr_fd("cd: ", 2);
    ft_putstr_fd(cmd->args[1], 2);
    ft_putstr_fd(str, 2);
}

static void change_dir(t_hmap **env, t_cmd_data *cmd)
{
	t_hmap	*temp;
	char	*path;

	temp = *env;
	if (!cmd->args[1])
	{
		temp = get_value_hmap(env, "HOME");
		if (!temp)
			ft_puterror(1, "HOME not set\n", cmd);
		else if (chdir(temp->value))
			ft_puterror(1, "can't move to HOME directory\n", cmd);
	}
	else
	{
		path = take_path(cmd->args[1]);
		if (chdir(path) < 0)
		{
    		cd_error(cmd, " : No such file or directory\n");
			exit(1); //will need to change the exit_code later
		}
		else
			exit(0); //will need to change the exit_code later
		free(path);
	}
}

void ft_cd(t_cmd_data *cmd, t_hmap **env)
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
		free(temp->value);
		temp->value = oldpwd; //maybe change_value() should be the way to do it
	}
	change_dir(env, cmd);
	temp = NULL;
	temp = get_value_hmap(env, "PWD");
	if (!temp)
	{
		add_new_var(env, "PWD", getcwd(NULL, 0));
		return ;
	}
	free(temp->value);
	temp->value = getcwd(NULL, 0);
	if (!temp->value)
		malloc_error();
}
