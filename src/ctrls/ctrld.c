// #include "../../headers/minishell.h"

// static volatile int	g_sigint_received = 1;

// void	sigquit_handler(int signum, t_cmd_data *c)
// {
// 	if (signum == SIGQUIT)
// 	{
// 		if (!is_interactive_mode())
// 		{
// 			printf("\33[2K\rQuit: 3\n");
// 			free_hmap(c->env_ptr->hashmap);
// 			exit(EXIT_SUCCESS);
// 		}
// 	}
// }

// void	ctrl_d_handler(char *str, t_cmd_data *c)
// {
// 	if (!str)
// 	{
// 		tcsetattr(STDIN_FILENO, TCSANOW, &(c->termio1));
// 		ft_putendl_fd("exit", 0);
// 		free_hmap(c->env_ptr->hashmap);
// 		exit(EXIT_SUCCESS);
// 	}
// }

// static void	sigint_handler(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		g_sigint_received = 1;
// 		ioctl(STDOUT_FILENO, TIOCSTI, "\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 	}
// }

// void	set_signals(t_cmd_data *c)
// {
// 	tcgetattr(STDIN_FILENO, &(c->termio1));
// 	c->termio2 = c->termio1;
// 	c->termio2.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &(c->termio2));
// 	signal(SIGINT, sigint_handler);
// 	// signal(SIGQUIT, sigquit_handler);
// }
