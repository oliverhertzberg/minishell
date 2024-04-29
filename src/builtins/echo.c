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

static void	handle_echo_str(char *input, int start, int end)
{
	// make this functions
}

static void	print_space(char *input, int i)
{
	if (input[i] != 0)
	{
		write(1, " ", 1);
		i++;
	}
}

static void	do_echo(char input, int i)
{
	char	quote;
	int	start;

	while (input[i] != 0)
	{
		while (ft_isspace(input[i]) == 1)
			i++;
		start = i;
		while (ft_isspace(input[i]) == 0 && input[i] != 0)
		{
			if (input[i] == '"' || input[i] == "'")
			{
				quote = input[i];
				while (input[i] != quote && input[i] != 0)
					i++;
				if (input[i] == quote)
					quote = 0;
			}
			i++;
		}
		handle_echo_str(input, start, i);
		print_space(input, i)
	}
}

void	ft_echo(char *input)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	quote = 0;
	if (check_word(input, i, ft_strlen(input)) == 0)
		// error
		return ;
	while (ft_isspace(input[i]) == 1)
		i++;
	if (ft_strncmp(input + i, "-n", 2) == 1)
	{
		i += 2;
		flag = 1;
	}
	do_echo(input, i)
	if (flag == 0)
		write(1, "\n", 1);
}
