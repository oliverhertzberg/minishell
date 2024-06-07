#include "../../headers/minishell.h"

int	g_sigint_received;

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sigint_received = 2;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signals(void)
{
	caret_switch(0);
	g_sigint_received = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_heredoc_signals(void)
{
	caret_switch(0);
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	caret_switch(int on)
{
	struct termios	termio;

	termio = (struct termios){0};
	tcgetattr(STDIN_FILENO, &termio);
	if (!on)
		termio.c_lflag &= ~ECHOCTL;
	else
		termio.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termio);
}

void	set_signals_from_parent(void)
{
	caret_switch(1);
	signal(SIGINT, sigint_handler_2);
	signal(SIGQUIT, sigquit_handler);
}
