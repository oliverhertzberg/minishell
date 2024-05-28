#include "../../headers/minishell.h"

void	heredoc_sigint(int signum)
{
	(void)signum;
	if (signum == SIGINT)
	{
		g_sigint_received = 1;
		// ft_putendl_fd("\33[2K\r>", 1);
		close(STDIN_FILENO);
	}
}

void	ctrl_d_handler(char *str, t_cmd_data *c)
{
	if (!str)
	{
		tcsetattr(STDOUT_FILENO, TCSANOW, &(c->termio1));
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

void	sigquit_from_parent_handler(int signum) //dont touch it
{
	if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	set_signals_from_parent(void) //dont touch it
{
	caret_switch(0);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, sigquit_from_parent_handler);
}
