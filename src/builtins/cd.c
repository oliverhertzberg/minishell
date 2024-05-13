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



static void change_dir(t_hmap **env, t_cmd_data *cmd)
{
	t_hmap	*temp;
	char	*path;

	temp = *env;
	if (!cmd->args[1])
	{
		temp = get_value_hmap(env, "HOME");
		if (!temp)

	}
	else
	{

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
		temp->value = oldpwd; //maybe change_value() shouldbe the way to do it
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
