#include "../../headers/builtins.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit(EXIT_FAILURE);
	else
		printf("%s\n", pwd);
}
