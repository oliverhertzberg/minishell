#include "../../headers/minishell.h"

void	handle_dollar52(int *j, int exit_code, char **new_str)
{
	char	*itoa_string;
	char	*temp;

	itoa_string = ft_itoa(exit_code);
	if (!itoa_string)
		exit(1);
	temp = ft_strdup(itoa_string);
	if (!temp)
		exit(1);
	*new_str = ft_strjoin_new(new_str, &temp);
	free (itoa_string);
	free (temp);
	(*j) += 2;
}
