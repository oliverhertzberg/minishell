// #include "../../headers/minishell.h"

static int	g_sigint_received = 0;

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

static void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sigint_received = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	set_signals(t_cmd_data *c)
{
	caret_switch(0);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_heredoc_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_sigint);
}

void	caret_switch(int on)
{
	struct termios	term;

	term = (struct termios){0};
	tcgetattr(STDIN_FILENO, &term);
	if (!on)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
