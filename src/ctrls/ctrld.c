#include "../../headers/minishell.h"

/*
typedef struct
{
    struct termios termio1;
    struct termios termio2;
} t_data;

t_data termios_data;

void ctrld(char *cmd, t_data termios)
{
    if (!cmd)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, (t_data.termio1));
		free_hmap(hmap);
		ft_putstr_fd("exit\n", 0, 1);
        exit(0);
    }
}*/

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
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}
/*
void sigquit_handler(int signum)
{
	(void)signum;
	printf("\n^Quit: 3...\n");
	// Clean up
	tcsetattr(STDIN_FILENO, TCSANOW, &(t_data.termio1));
	exit(0);
}*/

/*void set_signal_handlers(int mode, t_hmap **hmap)
{
	tcgetattr(STDIN_FILENO, &(t_data.termio1));
	t_data.termio2 = t_data.termio1;
	t_data.termio2.c_lflag &= ~ECHOCTL;
	if(mode == 2)
		t_data.termio2.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &(t_data.termio2));
	if (mode == 0 || mode == 1)
	{
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
        signal(SIGINT, sigquit_handler);
        signal(SIGQUIT, sigquit_handler);
	}
}*/

void	signaltrying(int mode)
{
	if (mode == 0)
	{
		g_sigint_received = 0; // Reset the signal received flag
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		caret_switch(1); // Turn on control character echo
	}
	else
		printf("mode is not zero");
}
