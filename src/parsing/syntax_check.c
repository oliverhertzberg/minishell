#include "../../headers/minishell.h"

char	*get_next_word(char *input, int *i)
{
	char	quote;
	int		start;
	int		end;

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
	return (ft_parse_substr(input, start, end - start));
}

int	count_redirections(char redir, char *word)
{
	int i;

	i = 0;
	while (word[i] && word[i] == redir)
		i++;
	return (i);
}

void	syntax_error_redir(char *word, int count, int is_pipe, int *parsing_error)
{
	if (word[0] == '<')
	{
		if (count == 1)
            write(1, "minishell: syntax error near unexpected token `<'\n", 51);
		else if (count == 2)
			write(1, "minishell: syntax error near unexpected token `<<'\n", 52);
		else if (count >= 3)
            write(1, "minishell: syntax error near unexpected token `<<<'\n", 53);
	}
	else if (word[0] == '>')
	{
		if (count == 1 && is_pipe)
            write(1, "minishell: syntax error near unexpected token `>|'\n", 52);
		else if (count == 1)
			write(1, "minishell: syntax error near unexpected token `>'\n", 51);
		else if (count >= 2)
			write(1, "minishell: syntax error near unexpected token `>>'\n", 52);
	}
    *parsing_error = 1;
}

void	syntax_error_special(char *word, int count, int is_pipe, int *parsing_error)
{
	if (word[0] == '|')
	{
		if (count == 1 && !is_pipe)
			write(1, "minishell: syntax error near unexpected token `|'\n", 51);
		else
			write(1, "minishell: syntax error near unexpected token `||'\n", 52);
	}
	else if (word[0] == '&')
	{
		if (count == 1)
			write(1, "minishell: syntax error near unexpected token `&'\n", 51);
		else if (count >= 2)
			write(1, "minishell: syntax error near unexpected token `&&'\n", 52);
	}
    *parsing_error = 1;
}

void	get_word(char *input, int *i, int *parsing_error, t_cmd_data **c)
{
    char *word;
	int count;
	int	is_pipe;

	is_pipe = 0;
	if ((word = get_next_word(input, i)) == NULL)
        error_exit(NULL, "malloc failed\n", c, 1);
	else if (word[0] == '\0')
    {
		write(1, "syntax error near unexpected token `newline'\n", 46);
        *parsing_error = 1;
    }
	else if (word[0] == '<' || word[0] == '>')
	{
		if (input[*i] == '|')
			is_pipe = 1;
		count = count_redirections(word[0], word);
		syntax_error_redir(word, count, is_pipe, parsing_error);
	}
	else if (word[0] == '&' || word[0] == '|')
	{
		if (input[*i] && input[*i + 1] == '|')
			is_pipe = 1;
		count = count_redirections(word[0], word);
		syntax_error_special(word, count, is_pipe, parsing_error);
	}
}

void	handle_redirection(char *input, int *i, int *parsing_error, t_cmd_data **c)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		*i += 2;
		get_word(input, i, parsing_error, c);
	}
	else if (input[*i] == '<')
	{
		*i += 1;
		get_word(input, i, parsing_error, c);
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		*i += 2;
		get_word(input, i, parsing_error, c);
	}
	else if (input[*i] == '>')
	{
		*i += 1;
		get_word(input, i, parsing_error, c);
	}
}

static int	count_words(char *input, int j, t_cmd_data **c)
{
	char	*word;
	int		count;
	int		i;

	i = j;
	count = 0;
	while (input[i] && input[i] != '|')
	{
		if (!(word = get_next_word(input, &i)))
            error_exit(NULL, "malloc failed\n", c, 1);
		if (word[0] == '<' || word[0] == '>' \
			|| word[0] == '|' || word[0] == '\0')
		{
			free (word);
			break ;
		}
		free (word);
		count++;
	}
	return (count);
}
// cat arg1 arg2 <Makefile arg3

void	handle_command(char *input, int *i, t_cmd_data **c)
{
	count_words(input, *i, c);
}

//       <Makefile cat -e | wc -l
// need to check here if c_env->syntax_error is 1
void	syntax_check(char *input, t_cmd_data **c)
{
	int			i;
    int         pipe;
    int         parsing_error = 0;

	i = 0;
    pipe = 2;
	while (input[i] && !parsing_error)
	{
		while (ft_isspace(input[i]) == 1)
			i++;
		if (input[i] == '|')
		{
            if (pipe == 2 || pipe == 1)
            {
                write(1, "minishell: syntax error near unexpected token `|'\n", 51);
                parsing_error = 1;
            }
            pipe = 1;
			i++;
			break ;
		}
        pipe = 0;
		if (input[i] == '<' || input[i] == '>')
			handle_redirection(input, &i, &parsing_error, c);
		else
			handle_command(input, &i, c);
	}
}
