#include "../headers/minishell.h"

// TESTING FUNCTIONS  to check t_parser variables

void	print_args(char **args)
{
	int i = 0;

	while (args[i])
	{
		printf("args[%d] = %s\n", i, args[i]);
		i++;
	}
}

void	print_file_list(t_file **list)
{
	t_file *current;

	current = *list;
	while (current)
	{
		printf("list file: %s\n", current->file);
		printf("list fd: %d\n", current->fd);
		printf("list append: %d\n", current->append);
		current = current->next;
	}
}

void	print_t_cmd_data(t_cmd_data **p)
{
	t_cmd_data *current;

	current = *p;
	while (current)
	{
		if (current->args)
			print_args(current->args);
		if (current->infile)
			print_file_list(&(current->infile));
		if (current->outfile)
			print_file_list(&(current->outfile));
		if (current->heredoc)
			print_file_list(&(current->heredoc));
		current = current->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_cmd_data	*c;
	t_cmd_env	c_env;

	if (argc != 1)
	{
		error_msg("There are no arguments!\n",
			"Run program with: ./minishell");
		return (1);
	}
	(void)argv;
	// adding env to c_env, since we dont have a function that turns hashmap back into
	// char * const * format
	init_c_env(&c_env, env);
	c_env.hashmap = init_hmap(env);
	if (!c_env.hashmap)
		return (1);
	add_shelllevel(c_env.hashmap);
	while (1)
	{
		input = readline("Minishell:$ ");
		signaltrying(0);
		printf("%s\n", input);
		c = lstnew(&c_env);
		parse_input(&c, input, &c_env); // go through each string, and get necessary variables for command table
		//print_t_cmd_data(&c); // print all struct variables for testing
		//do_builtins(c, c_env);
		execution(&c, &c_env);
		// cleaning strings based on quotes and spaces
		// taking informations or printing errors if needed and freeing everything
		// using pipex or builtings or both :)
		//add_history(input);
		free(input);
	}
	return (0);
}
