#include "../../headers/minishell.h"

void	sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("\33[2K\r>", 1);
		close(STDIN_FILENO);
	}
}

void	sigquit_handler(char *str, t_cmd_data *c)
{
	if (!str)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &(c->termio1));
		ft_putendl_fd("exit", 1);
		free_hmap(c->env_ptr->hashmap);
		exit(EXIT_SUCCESS);
	}
}

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sigint_received = 1;
		ioctl(STDOUT_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	set_signals(t_cmd_data *c)
{
	tcgetattr(STDIN_FILENO, &(c->termio1));
	c->termio2 = c->termio1;
	c->termio2.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &(c->termio2));
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
