#include "../../headers/builtins.h"

void	print_space(t_builtins *b, int i)
{
	if (b->value[i] != 0)
	{
		write(1, " ", 1);
		i++;
	}
}

void	print_string(t_builtins *b, int start, int end) //check this
{
	while (start < end)
	{
		write(1, &b->value[start], 1);
		start++;
	}
}

void	handle_dolar(t_builtins *b, int start, int end)
{
	
}

void	handle_mix(t_builtins *b, int start, int end)
{
	
}
