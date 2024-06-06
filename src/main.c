#include "../headers/minishell.h"

static void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("args[%d] = %s\n", i, args[i]);
		i++;
	}
}

static void	print_file_list(t_file **list)
{
	t_file	*current;

	current = *list;
	while (current)
	{
		printf("list file: %s\n", current->file);
		printf("list fd: %d\n", current->fd);
		printf("list append: %d\n", current->append);
		current = current->next;
	}
}

static void	arg_check_init(int argc, char **argv, t_cmd_env *c_env, char **env)
{
	if (argc != 1)
	{
		error_msg("There are no arguments!\n",
			"Run program with: ./minishell");
		exit(EXIT_FAILURE);
	}
	(void)argv;
	init_c_env(c_env, env);
}

static void	print_t_cmd_data(t_cmd_data **p)
{
	t_cmd_data	*current;

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
	t_cmd_data	*c;
	t_cmd_env	c_env;

	arg_check_init(argc, argv, &c_env, env);
	while (1)
	{
		set_signals();
		c_env.input = readline("Minishell:$ ");
		add_history(c_env.input);
		c = lstnew(&c_env);
		ctrl_d_handler(c_env.input, &c);
		if (!(parser(&c, &c_env, c_env.input)))
			continue ;
		if (g_sigint_received != 2)
		{
			set_signals_from_parent();
			execution(&c, &c_env);
		}
		else
		{
			free_t_cmd_data(&c, 1);
			free_t_cmd_env(&c_env);
		}
	}
	return (0);
}
