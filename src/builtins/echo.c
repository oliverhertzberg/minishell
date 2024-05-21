#include "../../headers/builtins.h"

/* 
if I have -n -nnn or any combination of it, it will skip them and
change flag to be 1, but if we get -nvrweverv (anything that's not n), 
it should still consider it as a string, not like -n and print it! 
*/
static void	new_line(t_cmd_data *d, int *i, int *flag)
{
	int	j;

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

/*
handling everything between single quotes
*/
static void	sq_echo(t_cmd_data *d, t_cmd_env e, int i)
{
	print_string(d->args[i], 0, -1);
}

/*
handling everything between double quotes
*/
static void	dq_echo(t_cmd_data *d, t_cmd_env e, int i)
{
	int	start;
	



}

/*
handling no quotes
*/
static void	nq_echo(t_cmd_data *d, t_cmd_env e, int i)
{
	char	quote;
	int	start;

	// while (d->args[*i] != 0)
	// {
	// 	while (ft_isspace(d->args[*i]) == 1)
	// 		i++;
	// 	start = i;
	// 	while (ft_isspace(d->args[*i]) == 0 && d->args[*i] != 0)
	// 	{
	// 		if (d->args[*i] == '"' || d->args[*i] == '\'')
	// 		{
	// 			quote = d->args[*i];
	// 			while (d->args[*i] != quote && d->args[*i] != 0)
	// 				i++;
	// 			if (d->args[*i] == quote)
	// 				quote = 0;
	// 		}
	// 		i++;
	// 	}
	// 	handle_echo_str(d->args[*i], start, i);
	// 	print_space(d->args[*i], i);
	// }
	
}

void	ft_echo(t_cmd_data *d, t_cmd_env e)
{
	int	i;
	int	j;
	int	flag;

	i = 1; //starts from 1, because 0 is builting name
	flag = 0; // we don't have -n option, and 1 if we do
	new_line(d, &i, &flag);
	while (d->args[i])
	{
		if (d->quote[i] == 0)
			nq_echo(d, e, i);
		else if (d->quote[i] == 1)
			sq_echo(d, e, i);
		else
			dq_echo(d, e, i);
		if (d->args[i])
			print_space(d, i);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}

