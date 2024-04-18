#include "../headers/minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)env;
	
	while (1)
	{
		input = readline("Minishell:$ ");
		ft_strip(&input);
		if (ft_strcmp(input, "pwd") == 0)
			ft_pwd();
		else if (ft_strncmp(input, "echo", 4) == 0)
			ft_echo(input);
		else
			printf("%s\n", input);
		add_history(input);
		free(input);
	}

	return (0);
}
