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
// static void	helping_function(char **str, int *i, int *j, char **new_str)
// {
// 	char	*temp;

// 	(*j)++;
// 	temp = single_quotes(str[*i], j);
// 	*new_str = ft_strjoin_new(new_str, &temp);
// 	free(temp);
// 	(*j)++;
// }
// static int	help_conditions(char **str, int *i)
// {
// 	if (is_in_str(str[*i], '\'', 0, ft_strlen(str[*i])) == -1
// 		&& is_in_str(str[*i], '"', 0, ft_strlen(str[*i])) == -1
// 		&& is_in_str(str[*i], '$', 0, ft_strlen(str[*i])) == -1)
// 		return (1);
// 	return (0);
// }

// void	clean_dolar(char **str, t_hmap  **h, int exit_code)
// {
// 	int		i;
// 	int		j;
// 	char	*new_str;
// 	char	*temp;

// 	i = 0;
// 	while (str[i] != NULL)
// 	{
// 		new_str = NULL;
// 		temp = NULL;
// 		if (help_conditions(str, &i) == 1)
// 			i++;
// 		else
// 		{
// 			j = 0;
// 			while (str[i][j])
// 			{
// 				if (str[i][j] == '\'')
// 					helping_function(str, &i, &j, &new_str);
// 				else if (str[i][j] == '"')
// 				{
// 					j++;
// 					temp = double_quotes(str[i], &j, h, exit_code);
// 					new_str = ft_strjoin_new(&new_str, &temp);
// 					free(temp);
// 					j++;
// 				}
// 				else
// 				{
// 					temp = no_quotes(str[i], &j, h, exit_code);
// 					new_str = ft_strjoin_new(&new_str, &temp);
// 					free(temp);
// 				}
// 			}
// 			free(str[i]);
// 			str[i] = ft_strdup(new_str);
// 			free(new_str);
// 			i++;
// 		}
// 	}
// }

static int	help_conditions(t_dollar *d, int *i)
{
	if (is_in_str(d->str[*i], '\'', 0, ft_strlen(d->str[*i])) == -1
		&& is_in_str(d->str[*i], '"', 0, ft_strlen(d->str[*i])) == -1
		&& is_in_str(d->str[*i], '$', 0, ft_strlen(d->str[*i])) == -1)
		return (1);
	return (0);
}

static void	helping_function(t_dollar *d, int *i, int *j)
{
	if (d->str[*i][*j] == '\'')
	{
		(*j)++;
		d->temp = single_quotes(d->str[*i], j);
		d->new_str = ft_strjoin_new(&(d->new_str), &(d->temp));
		free(d->temp);
		(*j)++;
	}
	else if (d->str[*i][*j] == '"')
	{
		(*j)++;
		d->temp = double_quotes(d->str[*i], j, d->h, d->ec);
		d->new_str = ft_strjoin_new(&(d->new_str), &(d->temp));
		free(d->temp);
		(*j)++;
	}
	else
	{
		d->temp = no_quotes(d->str[*i], j, d->h, d->ec);
		d->new_str = ft_strjoin_new(&(d->new_str), &(d->temp));
		free(d->temp);
	}
}

static void	skip_dsquotes(char **str, int *i, char **new_str, char **temp)
{
	if (ft_strcmp(str[*i], "\"\"") == 0 || ft_strcmp(str[*i], "''") == 0)
	{
		free(str[*i]);
		str[*i] = ft_strdup("");
		(*i)++;
	}
	*new_str = NULL;
	*temp = NULL;
}

void	clean_dlr(char **str, t_hmap	**h, int exit_code)
{
	t_dollar	d;
	int			i;
	int			j;

	i = 0;
	d.str = str;
	d.h = h;
	d.ec = exit_code;
	while (d.str[i] != NULL)
	{
		skip_dsquotes(d.str, &i, &(d.new_str), &(d.temp));
		if (d.str[i] == NULL)
			break ;
		if (help_conditions(&d, &i) == 1)
			(i)++;
		else
		{
			j = 0;
			while (str[i][j])
				helping_function(&d, &i, &j);
			free(d.str[i]);
			d.str[i++] = ft_strdup(d.new_str);
			free(d.new_str);
			//i++;
		}
	}
}
