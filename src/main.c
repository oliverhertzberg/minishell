#include "../headers/minishell.h"

void	initialize_t_parser(t_parser **p) // fix this! infinite loop when we run it!
{
	t_parser *current;
	
	current = *p;
	while (current)
	{
		current->is_here_doc = 0;
		current->fd_in = -2;
		current->fd_out = -2;
		current->append = 0;
		current->heredoc = NULL;
		current->infile = NULL;
		current->outfile = NULL;
		current->cmd_path = NULL;
		current->args = NULL;
		current = current->next;
	}
}

// TESTING FUNCTION  to check t_parser variables

void	print_args(char **args)
{
	int i = 0;

	while (args[i])
	{
		printf("args[%d] = %s\n", i, args[i]);
		i++;
	}
}

void	print_t_parser(t_parser **p)
{
	t_parser *current;

	current = *p;
	while (current)
	{
		printf("string = %s\n", current->string);
		print_args(current->args);
		current = current->next;
	}
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	t_hmap	**hashmap;
	t_parser **p;

	if (argc != 1)
	{
		error_msg("There are no arguments!\n",
			"Run program with: ./minishell");
		return (1);
	}
	(void)argv;
	hashmap = init_hmap(env);
	if (!hashmap)
		return (1);
	//add_shelllevel(hashmap); //this is seg faulting
	while (1)
	{
		p = (t_parser **)malloc(sizeof(t_parser *));
		input = readline("Minishell:$ ");
		printf("%s\n", input);
		ft_strip(&input); // removes spaces before and after input
		split_by_pipe(p, input); // split input by pipes into separate strings
		//printf("1\n");
		initialize_t_parser(p);
		//printf("2\n");
		// ft_exit(hashmap, p, 2);
		parse_string(p); // go through each string, and get necessary variables for command table
		print_t_parser(p);
		// cleaning strings based on quotes and spaces
		// taking informations or printing errors if needed and freeing everything
		// using pipex or builtings or both :)
		free_t_parser(p); //segfaults
		add_history(input);
		free(input);
	}
	return (0);
}
