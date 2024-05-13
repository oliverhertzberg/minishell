#include "../../headers/builtins.h"
/*
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
}*/

static void	print_space(t_cmd_data *d, int i)
{
	if (d->args[i])
	{
		write(1, " ", 1);
		i++;
	}
}

/* printing string from start to end position or to the end of string
if end == -1 */
static void	print_string(t_cmd_data *d, int i, int start, int end)
{
	while (d->args[i][start] != 0 && (start < end || end == -1))
	{
		write(1, &d->args[i][start], 1);
		start++;
	}
}

/*
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
		printf("%s", return_value_hash(b->h, key));
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
		if (b->value[start] == '$')
		{
			start++;
			dolar_help(b, &start, end);
		}
	}
}

void	handle_mix(t_builtins *b, int start, int end)
{
	
}
*/

static void	new_line(t_cmd_data *d, int *i, int *flag)
{
	int	j;

	/* if I have -n -nnn or any combination of it, it will skip them and
	change flag to be 1, but if we get -nvrweverv (anything that's not n), 
	it should still consider it as a string, not like -n and print it! */
	while (ft_strncmp(d->args[*i], "-n", 2) == 1)
	{
		j = 2;
		while (d->args[*i][j] == 'n')
			j++;
		if (d->args[*i][j] == 0)
			*flag = 1;
		else
			break ;
		(*i)++;
	}
}

static void	do_echo(t_cmd_data *d, int *i)
{

}

void	ft_echo(t_cmd_data *d)
{
	int	i;
	int	j;
	int	flag;

	i = 1; //starts from 1, because 0 is builting name
	flag = 0; // we don't have -n option, and 1 if we do
	new_line(d, &i, &flag);
	while (d->args[i])
	{
		do_echo(d, &i);
		print_space(d, i);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}

