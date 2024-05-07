#include "../headers/minishell.h"

void	initialize_t_parser(t_parser **p) // fix this! infinite loop when we run it!
{
	t_parser *current;
	int num_of_cmds;

	num_of_cmds = 0;
	current = *p;
	while (current)
	{
		current->fd_here_doc = -2;
		current->fd_in = -2;
		current->fd_out = -2;
		current->append = 0;
		current->infile = NULL;
		current->outfile = NULL;
		current->cmd_path = NULL;
		current->args = NULL;
		num_of_cmds++;
		current = current->next;
	}
	(*p)->num_of_cmds = num_of_cmds;
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	t_hmap	**hashmap;
	t_parser **p;

	(void)argc;
	(void)argv;
	hashmap = init_hmap(env);
	if (!hashmap)
		return (1);
	while (1)
	{
		p = (t_parser **)malloc(sizeof(t_parser *));
		input = readline("Minishell:$ ");
		ft_strip(&input); // removes spaces before and after input
		split_by_pipe(p, input); // split input by pipes into separate strings
		//initialize_t_parser(p);
		//parse_string(p); // go through each string, and get necessary variables for command table
		// cleaning strings based on quotes and spaces
		// taking informations or printing errors if needed and freeing everything
		// using pipex or builtings or both :) 
		// free everything
		
		add_history(input);
		free(input);
	}
	return (0);
}
