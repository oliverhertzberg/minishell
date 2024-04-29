#include "../../headers/builtins.h"

/* we should change it to work with export and unset also!
 * this is doing the simpest stuff, with just printing string and 
 * with option -n, but not if we have some variable set with export! 
 * also it is working for only one space between it, not more!
 * in case we fine $, we should check what is next to it and do we have that
 * string in key, if not, we skip it, if we do, then we skip it and print value
 * that is in hashmap with that key
 * if there is $ and space, we print that $
 * we should separatly look at the case when we have $(something), 
 * because that something is threated as command and print error if that command
 * doesn't exist! */

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
			if (b->value[i] == '"' || b->value[i] == "'")
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
		print_space(b->value, i)
	}
}

void	ft_echo(t_builtins *b)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	quote = 0;
	if (check_word(b->value, i, ft_strlen(b->value)) == 0)
		// error
		return ;
	while (ft_isspace(b->value[i]) == 1)
		i++;
	if (ft_strncmp(b->value + i, "-n", 2) == 1)
	{
		i += 2;
		flag = 1;
	}
	do_echo(b->value, i)
	if (flag == 0)
		write(1, "\n", 1);
}
