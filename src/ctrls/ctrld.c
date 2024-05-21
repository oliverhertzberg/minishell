#include "../../headers/minishell.h"

static int	g_sigint_received = 0;

void	caret_switch(int on)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (!on)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_sigint_received == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			caret_switch(0);
			g_sigint_received = 1;
		}
		else
			write(STDOUT_FILENO, "Minishell:$\n", 12);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signaltrying(int mode)
{
	if (mode == 0)
	{
		g_sigint_received = 0; // Reset the signal received flag
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		caret_switch(1); // Turn on control character echo
	}
}
