#include "../../headers/builtins.h"

char	*ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit(EXIT_FAILURE); //handle it
	printf("%s\n", pwd);
	return (pwd);
}
