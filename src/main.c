#include "../headers/minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*input;
	t_var	hashmap;
	t_parser *p;

	(void)argc;
	(void)argv;
	
	//filling hashmap with env values and checking if env is emptly!
	while (1)
	{
		input = readline("Minishell:$ ");
		ft_strip(&input);
		split_parser(&p, input);
		// cleaning strings based on quotes and spaces
		// taking informations or printing errors if needed and freeing everything
		// using pipex or builtings or both :) 
		// free everything
		
		add_history(input);
		free(input);
	}
	return (0);
}
