#include "../headers/minishell.h"

void	initialize_t_parser(t_parser **p)
{
	
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	t_hmap	**hashmap;
	t_parser *p;

	(void)argc;
	(void)argv;
	
	//filling hashmap with env values and checking if env is emptly!
	while (1)
	{
		input = readline("Minishell:$ ");
		ft_strip(&input); // removes spaces before and after input
		split_by_pipe(&p, input); // split input by pipes into separate strings
		initialize_t_parser();
		parse_string(&p); // go through each string, and get necessary variables for command table
		// cleaning strings based on quotes and spaces
		// taking informations or printing errors if needed and freeing everything
		// using pipex or builtings or both :) 
		// free everything
		
		add_history(input);
		free(input);
	}
	return (0);
}
