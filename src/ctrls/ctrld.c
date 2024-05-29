#include "../../headers/minishell.h"

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sigint_received = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signals(void)
{
	if (g_sigint_received == 1)
	{
		write(1, "\n", 1);
		g_sigint_received = 0;
	}
	caret_switch(0);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	g_sigint_received = 1;
}

void	set_heredoc_signals(void)
{
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

void	set_signals_from_child(void)
{
	caret_switch(1);
	signal(SIGINT, sigint_from_child_handler);
	signal(SIGQUIT, SIG_DFL);
}
