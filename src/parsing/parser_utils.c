#include "../../headers/minishell.h"

static char	*check_next_word(char *input, int i)
{
	char	quote;
	int		start;
	int		end;
	char	*word;

	quote = '\0';
	while (input[i] && ft_isspace(input[i]) == 1)
		(i)++;
	if (input[i] == '|')
		return (ft_strdup("|"));
	start = i;
	while (input[i])
	{
		if (!quote && (ft_isspace(input[i]) == 1 || input[i] == '|'))
			break ;
		if (!quote && (input[i] == '\'' || input[i] == '"'))
			quote = input[i];
		else if (quote && input[i] == quote)
			quote = '\0';
		(i)++;
	}
	end = i;
	word = ft_parse_substr(input, start, end - start);
	return (word);
}

int	is_next_word_redirect(char *input, int i)
{
	char	*word;

	word = check_next_word(input, i);
	if (word[0] == '<' || word[0] == '>')
		return (1);
	return (0);
}

char	*get_next_word(char *input, int *i)
{
	char	quote;
	int		start;
	int		end;
	char	*word;

	quote = '\0';
	while (input[*i] && ft_isspace(input[*i]) == 1)
		(*i)++;
	if (input[*i] == '|')
		return (ft_strdup("|"));
	start = *i;
	while (input[*i])
	{
		if (!quote && (ft_isspace(input[*i]) == 1 || input[*i] == '|'))
			break ;
		if (!quote && (input[*i] == '\'' || input[*i] == '"'))
			quote = input[*i];
		else if (quote && input[*i] == quote)
			quote = '\0';
		(*i)++;
	}
	end = *i;
	word = ft_parse_substr(input, start, end - start);
	return (word);
}

void	get_word(char **word, t_cmd_data **c, char *input, int *i)
{
	*word = get_next_word(input, i);
	if (!(*word))
		error_exit(NULL, "malloc failed\n", c, 1);
	else if ((*word)[0] == '\0')
		(*c)->env_ptr->parsing_error = 1;
	else if ((*word)[0] == '<' || (*word)[0] == '>')
		(*c)->env_ptr->parsing_error = 1;
	else if ((*word)[0] == '&' || (*word)[0] == '|')
		(*c)->env_ptr->parsing_error = 1;
}
