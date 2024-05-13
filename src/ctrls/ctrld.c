#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

// Structure to store terminal settings
typedef struct {
    struct termios termio1;
    struct termios termio2;
} t_data;

void set_signal_handlers(int mode, t_hmap **hmap)
{
	tcgetattr(STDIN_FILENO, &(t_data->termio1));
	t_data->termio2 = t_data->termio1;
	t_data->termio2.c_lflag &= ~ECHOCTL;
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
