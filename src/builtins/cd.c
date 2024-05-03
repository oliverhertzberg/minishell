#include "../../headers/minishell.h"

//access(const char *pathname, int mode): checks whether the calling process has the specified mode of access permissions to the file or directory specified by pathname.
//If the file or directory does not exist or the calling process lacks the necessary permissions, access() returns -1
//F_OK: to check if the file exists

//chdir((char *path)) returning 0 on success and -1 on failure
//input = av[1]
//getenv retrieves the value of the environment variable named name.
static int does_not_exist(char *path)
{
	int is_accessible;

	is_accessible = access(path, F_OK);
	if (is_accessible < 0)
		return (1);
	return (0);
}
static int is_a_directory(char *path)
{
	int fd;

	fd = open(path, O_DIRECTORY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static void free_path_pwd(char **pwd, char **path)
{
	free(pwd);
	free(path);
}

static void error_path(char **oldpwd, char *input, t_hmap **env)
{
	if (*oldpwd)
		update_dir("opwd", oldpwd, env);
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(input, 2);
	if (does_not_exist(input))
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (!does_not_exist(input) && !is_a_directory(input))
		ft_putstr_fd(": Not a directory\n", 2);
}

void ft_cd(char *input, t_hmap **env)
{
	char	*pwd;
	char	*oldpwd;
	char	*path;

	if (!input)
		path = ft_strdup(getenv("HOME"));
	else
		path = ft_strdup(input);
	pwd = ft_pwd();
	oldpwd = getenv("OLDPWD");
	if (already_in_list("OLDPWD", *env))
		update_dir("opwd", pwd, env);
	if (does_not_exist(path) || chdir(path) < 0)
	{
		error_path(&oldpwd, path, env);
		free_path_pwd(&pwd, &path);
		return ;
	}
	free(pwd);
	pwd = ft_pwd();
	if (already_in_list("PWD", *env))
		update_dir("pwd", pwd, env);
	free_path_pwd(&pwd, &path);
}
