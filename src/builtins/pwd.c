#include "../../headers/builtins.h"

char	*ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("getcwd() error"));
	printf("%s\n", pwd);
	return (pwd);
}
