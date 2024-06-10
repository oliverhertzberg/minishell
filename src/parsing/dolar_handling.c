#include "../../headers/minishell.h"

char	*single_quotes(char *str, int *j)
{
	char	*new_str;
	int		start;

	start = *j;
	while (str[*j] != 0 && str[*j] != '\'')
		(*j)++;
	new_str = ft_substr(str, start, *j - start);
	return (new_str);
}

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
	char	*exit_code;

	if (d->str[*i][*j] == '\'')
		handle_single_quotes(d, i, j);
	else if (d->str[*i][*j] == '"')
	{
		(*j)++;
		exit_code = ft_itoa(d->ec);
		if (!exit_code)
			exit (1);
		d->temp = double_quotes(d->str[*i], j, d->h, exit_code);
		d->new_str = ft_strjoin_new(&(d->new_str), &(d->temp));
		free (exit_code);
		free(d->temp);
		(*j)++;
	}
	else
	{
		exit_code = ft_itoa(d->ec);
		if (!exit_code)
			exit (1);
		d->temp = no_quotes(d->str[*i], j, d->h, exit_code);
		d->new_str = ft_strjoin_new(&(d->new_str), &(d->temp));
		free (exit_code);
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
		}
	}
}
