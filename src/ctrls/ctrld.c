#include "../../headers/minishell.h"

// void	caret_switch(int on)
// {
// 	struct termios	term;

// 	tcgetattr(STDIN_FILENO, &term);
// 	if (!on)
// 		term.c_lflag &= ~ECHOCTL;
// 	else
// 		term.c_lflag |= ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

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
		// caret_switch(0);
		rl_on_new_line();
		rl_replace_line("", 0);
		// rl_redisplay();
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
	// caret_switch(1); // Turn on control character echo
}

// static void    sigint_handler(int sig)
// {
//     if (sig == SIGINT)
//     {
//         printf("\33[2K\rMinishell:$\n");
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//     }
// }

// void    set_signals(void)
// {
//     signal(SIGINT, sigint_handler);
//     signal(SIGQUIT, SIG_IGN);
// }
