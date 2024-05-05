#include "../../headers/builtins.h"

static void	handle_echo_str(t_builtins *b, int start, int end)
{
	if (is_inside_quotes(b->value, start, end) == 0 && is_in_str(b->value, '$', start, end) == -1)
		print_string(b, start, end);
	else if (is_inside_quotes(b->value, start, end) == 0)
		handle_dolar(b, start, end);
	else if ((is_inside_quotes(b->value, start, end) == 2)
		|| (is_inside_quotes(b->value, start, end) == 1 && is_in_str(b->value, '$', start, end) == -1))
		print_string(b, start + 1, end - 1);
	else if (is_inside_quotes(b->value, start, end) == 1)
		handle_dolar(b, start + 1, end - 1);
	else
		handle_mix(b, start, end);
}

static void	do_echo(t_builtins *b, int i)
{
	char	quote;
	int	start;

	while (b->value[i] != 0)
	{
		while (ft_isspace(b->value[i]) == 1)
			i++;
		start = i;
		while (ft_isspace(b->value[i]) == 0 && b->value[i] != 0)
		{
			if (b->value[i] == '"' || b->value[i] == '\'')
			{
				quote = b->value[i];
				while (b->value[i] != quote && b->value[i] != 0)
					i++;
				if (b->value[i] == quote)
					quote = 0;
			}
			i++;
		}
		handle_echo_str(b->value, start, i);
		print_space(b->value, i);
	}
}

static void	new_line(t_builtins *b, int *i, int *flag)
{
	while (b->value[*i] != 0)
	{
		while (ft_isspace(b->value[*i]) == 1)
			(*i)++;
		if (ft_strncmp(b->value + i, "-n", 2) == 1
				&& (ft_isspace(b->value[*i + 2]) == 1 || b->value[*i + 2] == 'n'
					|| b->value[*i + 2] == 0))
		{
			i += 2;
			*flag = 1;
			while (b->value[*i] == 'n')
				(*i)++;
		}
	}
}

void	ft_echo(t_builtins *b)
{
	int	i;
	int	flag;
	int quote;

	i = 0;
	flag = 0;
	quote = 0;
	if (check_word(b->value, i, ft_strlen(b->value)) == 0)
		// error
		return ;
<<<<<<< HEAD
	new_line(b, &i, &flag);
	do_echo(b->value, i)
=======
	while (ft_isspace(b->value[i]) == 1)
		i++;
	if (ft_strncmp(b->value + i, "-n", 2) == 1)
	{
		i += 2;
		flag = 1;
	}
	do_echo(b->value, i);
>>>>>>> cc411b2d99229430e5c60035525e9ddf96a1caee
	if (flag == 0)
		write(1, "\n", 1);
}
