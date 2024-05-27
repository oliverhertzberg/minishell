// #include "../../headers/minishell.h"

// void	sigint_heredoc(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		ft_putendl_fd("\33[2K\r>", 1);
// 		close(STDIN_FILENO);
// 	}
// }

// int	is_interactive_mode(void)
// {
// 	return (isatty(STDIN_FILENO)); //returns 1 if it's in interactive mode
// }

// void	default_signals(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }
