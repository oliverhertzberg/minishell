#include "../../headers/minishell.h"

void	heredoc_sigint(int signum)
{
	(void)signum;
	if (signum == SIGINT)
		g_sigint_received = 1;
	ft_putstr("\n");
	close(STDIN_FILENO);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_from_child_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	sigint_from_parent_handler(int signum)
{
	if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	set_signals_from_child(void)
{
	caret_switch(1);
	signal(SIGINT, sigint_from_child_handler);
	signal(SIGQUIT, SIG_DFL);
}

// void	standby_signals(void)
// {
// 	caret_switch(1);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, SIG_IGN);
// }
