#include "../../headers/minishell.h"
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

// Structure to store terminal settings
typedef struct {
    struct termios termio1;
    struct termios termio2;
} t_data;

void ctrld(char *cmd, t_data termios)
{
    if (!cmd)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, (t_data->termio1));
	free_hmap(hmap);
	ft_putstr_fd("exit\n", 0, 1);
        exit(0);
    }
}

void sigint_handler(int signum)
{
	if(signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void sigquit_handler(int signum)
{
    printf("\n^Quit: 3...\n");
    // Clean up
    exit(0);
}

void set_signal_handlers(int mode, t_hmap **hmap)
{
	tcgetattr(STDIN_FILENO, &(t_data->termio1));
	t_data->termio2 = t_data->termio1;
	t_data->termio2.c_lflag &= ~ECHOCTL;
	if(mode == 2)
		t_data->termio2.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &(t_data->termio2));
	if (mode == 0)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, sigquit_handler);
		signal(SIGQUIT, sigquit_handler);
	}
}
