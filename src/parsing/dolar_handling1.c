#include "../../headers/minishell.h"

/*
cleaning double quotes
*/
static void	help_funct(char *str, char **new_str, int *j, t_hmap **h)
{
	char	*temp;
	int		start;
	char	*value;

	temp = NULL;
	start = *j;
	while (str[*j] != 0 && str[*j] != '\'' && str[*j] != '"'
		&& ((ft_isalpha(str[*j]) == 1 || str[*j] == '_'
				|| ft_isdigit(str[*j]) == 1)))
		(*j)++;
	temp = ft_substr(str, start, *j - start);
	if (return_value_hash(*h, temp) != NULL)
	{
		value = ft_strdup(return_value_hash(*h, temp));
		free(temp);
		*new_str = ft_strjoin_new(new_str, &value);
		free(value);
	}
}

static void	dollar_cleaning_dq(char *str, char **new_str, int *j, t_hmap **h)
{
	char	*temp;

	(*j)++;
	temp = NULL;
	if (str[*j] == 0 || str[*j] == '\'' || str[*j] == '"'
		|| (ft_isalpha(str[*j]) == 0 && str[*j] != '_'
			&& ft_isdigit(str[*j]) == 0))
	{
		temp = ft_strdup("$");
		*new_str = ft_strjoin_new(new_str, &temp);
		free(temp);
	}
	else if (ft_isdigit(str[*j]) == 1)
		(*j)++;
	else
		help_funct(str, new_str, j, h);
}

static void	no_dollar(char *str, int *j, char **new_str)
{
	char	*temp;
	int		start;

	if (str[*j] != '$')
	{
		start = *j;
		while (str[*j] != 0 && str[*j] != '"' && str[*j] != '$')
			(*j)++;
		temp = ft_substr(str, start, *j - start);
		*new_str = ft_strjoin_new(new_str, &temp);
	}
}

char	*double_quotes(char *str, int *j, t_hmap **h, char *exit_code)
{
	char	*new_str;
	char	*temp;

	new_str = NULL;
	while (str[*j] != 0 && str[*j] != '"')
	{
		temp = NULL;
		no_dollar(str, j, &new_str);
		if (str[*j] == '$')
		{
			if (str[*j + 1] == '?')
			{
				temp = ft_strdup(exit_code);
				free (exit_code);
				new_str = ft_strjoin_new(&new_str, &temp);
				(*j) += 2;
			}
			else
				dollar_cleaning_dq(str, &new_str, j, h);
		}
		if (temp != NULL)
			free(temp);
	}
	return (new_str);
}
