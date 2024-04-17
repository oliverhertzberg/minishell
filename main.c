#include "headers/minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argc;
	(void)argv;
	input = readline("Enter yoour text: \n");
	
	if (input)
	{
		printf("%s\n", input);
		add_history(input);
		free(input);
	}

	return (0);
}
