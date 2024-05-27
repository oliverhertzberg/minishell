#include "../../headers/minishell.h"

static int	g_sigint_received = 0;

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

void	set_signals(void)
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
	struct termios	termio;

	termio = (struct termios){0};
	tcgetattr(STDIN_FILENO, &termio);
	if (!on)
		termio.c_lflag &= ~ECHOCTL;
	else
		termio.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termio);
}
