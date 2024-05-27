#include "../../headers/minishell.h"

void	heredoc_sigint(int signum)
{
	(void)signum;
	if (signum == SIGINT)
		g_sigint_received = 1;
	ft_putstr_fd("\n", STDOUT_FILENO);
	close(STDIN_FILENO);
}

// void	ignore_signals(void)
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// }

void	ctrl_d_handler(char *str, t_cmd_data *c)
{
	if (!str)
	{
		tcsetattr(STDOUT_FILENO, TCSANOW, &(c->termio));
		ft_putendl_fd("exit", 0);
		free_hmap(c->env_ptr->hashmap);
		exit(EXIT_SUCCESS);
	}
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
