#include "../../headers/minishell.h"

static char	*single_quotes(char *str, int *j)
{
	char	*new_str;
	int		start;

	start = *j;
	while (str[*j] != 0 && str[*j] != '\'')
		(*j)++;
	new_str = ft_substr(str, start, *j - start);
	return (new_str);
}

void	clean_dolar(char **str, t_hmap  **h, int exit_code)
{
	int		i;
	int		j;
	char	*new_str;
	char	*temp;
	char	*temp1;

	i = 0;
	while (str[i] != NULL)
	{
		new_str = NULL;
		temp = NULL;
		temp1 = NULL;
		if (check_word(str[i], 0, ft_strlen(str[i])) == 0)
		// open quotes error
			exit(EXIT_FAILURE);
		if (is_in_str(str[i], '\'', 0, ft_strlen(str[i])) == -1
			&& is_in_str(str[i], '"', 0, ft_strlen(str[i])) == -1
			&& is_in_str(str[i], '$', 0, ft_strlen(str[i])) == -1)
			i++;
		else
		{
			j = 0;
			while (str[i][j])
			{
				if (str[i][j] == '\'')
				{
					j++;
					temp = single_quotes(str[i], &j);
					new_str = ft_strjoin_new(&new_str, &temp);
					free(temp);
					j++;
				}
				else if (str[i][j] == '"')
				{
					j++;
					temp = double_quotes(str[i], &j, h, exit_code);
					new_str = ft_strjoin_new(&new_str, &temp);
					free(temp);
					j++;
				}
				else
				{
					temp = no_quotes(str[i], &j, h, exit_code);
					new_str = ft_strjoin_new(&new_str, &temp);
					free(temp);
				}
			}
			free(str[i]);
			str[i] = ft_strdup(new_str);
			free(new_str);
			i++;
		}
	}
}
