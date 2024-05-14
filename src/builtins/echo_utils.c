#include "../../headers/builtins.h"

// void	print_space(t_cmd_data *d, int i)
// {
// 	if (d->args[i])
// 	{
// 		write(d->fd_out, " ", 1);
// 		i++;
// 	}
// }

// /* printing string from start to end position or to the end of string
// if end == -1 */
// void	print_string(t_cmd_data *d, int i, int start, int end)
// {
// 	while (d->args[i][start] != 0 && (start < end || end == -1))
// 	{
// 		write(d->fd_out, &d->args[i][start], 1);
// 		start++;
// 	}
// }


// // change these functions!!!!
// static void	dolar_help(char *input, t_cmd_env e, int *start, int end)
// {
// 	int	pos;
// 	int	i;
// 	char	*key;

// 	pos = *start;		
// 	while (input[*start] != 0 && *start < end && ft_isspace(input[*start]) == 0)
// 		*start++;
// 	key = malloc(*start - end + 1);
// 	if (!key)
// 	{
// 		//malloc error
// 		return ;
// 	}
// 	i = 0;
// 	while (pos < *start)
// 	{
// 		key[i] = input[*start];
// 		i++;
// 		pos++;
// 	}
// 	key[i] = 0;
// 	if (key_exists(h, key) == 1)
// 		printf("%s", return_value_hash(h, key));
// 	free(key);
// }

// void	handle_dolar(char *input, t_cmd_env e, int start, int end) //check if I missed something
// {
// 	while (start < end)
// 	{
// 		while (input[start] != '$' && input[start] != 0 && (start < end || end == -1))
// 		{
// 			write(d->fd_out, &input[start], 1);
// 			start++;
// 		}
// 		if (input[start] == '$')
// 		{
// 			start++;
// 			dolar_help(input, h, &start, end);
// 		}
// 	}
// }