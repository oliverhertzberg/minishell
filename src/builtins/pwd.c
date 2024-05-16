#include "../../headers/builtins.h"

//maybe it needs to change back to be char ft_pwd
void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit(EXIT_FAILURE); //handle it
	else
		printf("%s\n", pwd);
	// return (pwd);
}
