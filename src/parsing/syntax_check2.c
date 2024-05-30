#include "../../headers/minishell.h"

static int	count_redirections(char redir, char *word)
{
	int	i;

	i = 0;
	while (word[i] && word[i] == redir)
		i++;
	return (i);
}

static void	syntax_error(char *word, int count, int is_pipe)
{
	if (word[0] == '<')
	{
		if (count == 1)
			psfd("minishell: syntax error near unexpected token `<'\n", 2);
		else if (count == 2)
			psfd("minishell: syntax error near unexpected token `<<'\n", 2);
		else if (count >= 3)
			psfd("minishell: syntax error near unexpected token `<<<'\n", 2);
	}
	else if (word[0] == '>')
	{
		if (count == 1 && is_pipe)
			psfd("minishell: syntax error near unexpected token `>|'\n", 2);
		else if (count == 1)
			psfd("minishell: syntax error near unexpected token `>'\n", 2);
		else if (count >= 2)
			psfd("minishell: syntax error near unexpected token `>>'\n", 2);
	}
	else if (word[0] == '|')
		psfd("minishell: syntax error near unexpected token `|'\n", 2);
}

void	get_word_syntax(char *input, int *i, int *parse_error, t_cmd_data **c)
{
	char	*word;
	int		count;
	int		is_pipe;

	is_pipe = 0;
	word = get_next_word(input, i);
	if (!word)
		error_exit(NULL, "malloc failed\n", c, 1);
	else if (word[0] == '\0')
		parsing_error("minishell: syntax error near \
			unexpected token `newline'\n", parse_error, c, 258);
	else if (word[0] == '<' || word[0] == '>' || word[0] == '|')
	{
		if (input[*i] == '|')
			is_pipe = 1;
		count = count_redirections(word[0], word);
		syntax_error(word, count, is_pipe);
		parsing_error(NULL, parse_error, c, 258);
	}
}

void	get_words_syntax(char *input, int *i, t_cmd_data **c)
{
	char	*word;

	while (input[*i] && input[*i] != '|')
	{
		word = get_next_word(input, i);
		if (!word)
			error_exit(NULL, "malloc failed \n", c, 1);
		if (word[0] == '<' || word[0] == '>' \
			|| word[0] == '|' || word[0] == '\0')
		{
			free (word);
			break ;
		}
		free (word);
	}
}

void	check_unclosed_quotes(int *s_error, char *input, t_cmd_data **c)
{
	int		i;
	char	quote;

	quote = '\0';
	i = -1;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (quote && input[i] == quote)
				quote = '\0';
			else if (!quote)
				quote = input[i];
		}
	}
	if (quote)
	{
		*s_error = 2;
		parsing_error(
			"minishell: syntax error: quotes not closed.\n",
			NULL, c, 258);
	}
}
