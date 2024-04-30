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

static void	dolar_help(t_builtins *b, int *start, int end)
{
	int	pos;
	int	i;
	char	*key;

	pos = *start;		
	while (b->value[*start] != 0 && *start < end && ft_isspace(b->value[*start]) == 0)
		*start++;
	key = malloc(*start - end + 1);
	if (!key)
	{
		//malloc error
		return ;
	}
	i = 0;
	while (pos < *start)
	{
		key[i] = b->value[*start];
		i++;
		pos++;
	}
	key[i] = 0;
	if (key_exists(b->h, key) == 1)
		printf("%s", return_value_hash(b->h, key))
	free(key);
}

void	handle_dolar(t_builtins *b, int start, int end) //check if I missed something
{
	while (start < end)
	{
		while (b->value[start] != '$' && b->value[start] != 0 && start < end)
		{
			write(1, &b->value[start], 1);
			start++;
		}
		if (b-value[start] == '$')
		{
			start++;
			dolar_help(b, &start, end);
		}
	}
}

void	handle_mix(t_builtins *b, int start, int end)
{
	
}
