#include "../../headers/builtins.h"

void	print_space(char *input, int i)
{
	if (input[i] != 0)
	{
		write(1, " ", 1);
		i++;
	}
}
