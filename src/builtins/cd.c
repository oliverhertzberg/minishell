#include "../../headers/minishell.h"


//chdir((char *path)) returning 0 on success and -1 on failure
//input = av[1]
//getenv retrieves the value of the environment variable named name.

int ft_cd(char *input, t_env **path)
{
	char	*pwd;
	char	*oldpwd;
	char	*path;

	if (!input)
		path = ft_strdup(getenv("HOME"));
	else
		path = ft_strdup(input);
	pwd = getcwd();
	oldpwd = getenv("OLDPWD");
	if (already_in_list(pwd, path))
		update_dir('')
	return (0);
}