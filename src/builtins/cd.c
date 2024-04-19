void	ft_cd(char *path)
{
	size_t	i;

	i = 0;
	while (path[i])
	{
		if (!ft_strcmp(path, "."))
		{

		}
		else if (!ft_strcmp(path, ".."))
		{

		}
		else if (!ft_strcmp(path, ""))
		{

		}
		else if ()
		i++;
	}
}

int	chdir_check(char *dir_path, int case)
{
	if (chdir(dir_path) == 0)
		return (1); //directory has successfully changed
	else
		return (0); //perror("chdir() error");
}