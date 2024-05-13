#include "../../headers/builtins.h"

void	print_space(t_cmd_data *d, int i)
{
	if (d->args[i])
	{
		write(1, " ", 1);
		i++;
	}
}

/* printing string from start to end position or to the end of string
if end == -1 */
void	print_string(t_cmd_data *d, int i, int start, int end)
{
	while (d->args[i][start] != 0 && (start < end || end == -1))
	{
		write(1, &d->args[i][start], 1);
		start++;
	}
}