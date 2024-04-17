#include "headers/minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)env;
	
	while (1)
	{
		input = readline("Minisell:$ ");
		if (ft_strcmp(input, "pwd") == 0)
			ft_pwd();
		else
			printf("%s\n", input);
		add_history(input);
		free(input);
	}

	return (0);
}
