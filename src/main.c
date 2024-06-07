#include "../headers/minishell.h"

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
			clear_structs(&c, 1, &c_env);
	}
	return (0);
}
