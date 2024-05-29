#include "../../headers/minishell.h"

void	free_and_exit(char *string_num, char *filename, t_cmd_data **c)
{
	free(string_num);
	free(filename);
	error_exit(NULL, "malloc failed\n", c, 1);
}
size_t	bytes_to_malloc(char *delimiter)
{
	int		i;
	size_t	bytes;
	char	quote;

	quote = '\0';
	bytes = 0;
	i = -1;
	while (delimiter[++i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
		{
			if (!quote)
				quote = delimiter[i];
			else if (quote == delimiter[i])
				quote = '\0';
			else
				bytes++;
		}
		else
			bytes++;
	}
	return (bytes);
}

void	trim_delimiter(char **trimmed, char *delimiter)
{
	char	quote;
	int		i;
	int		j;

	quote = '\0';
	i = -1;
	j = 0;
	while (delimiter[++i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
		{
			if (!quote)
				quote = delimiter[i];
			else if (quote == delimiter[i])
				quote = '\0';
			else
				(*trimmed)[j++] = delimiter[i];
		}
		else
			(*trimmed)[j++] = delimiter[i];
	}
	(*trimmed)[j] = '\0';
}

void	free_delim_and_filename(char *delimiter, char *filename)
{
	free (delimiter);
	free(filename);
}
