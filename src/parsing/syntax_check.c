#include "../../headers/minishell.h"

int	count_redirections(char redir, char *word)
{
	int i;

	i = 0;
	while (word[i] && word[i] == redir)
		i++;
	return (i);
}

void	syntax_error(char *word, int count, int is_pipe)
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
	else if (word[0] == '|')
		write(1, "minishell: syntax error near unexpected token `|'\n", 51);
}

void	get_word_syntax(char *input, int *i, int *parse_error, t_cmd_data **c)
{
    char *word;
	int count;
	int	is_pipe;

	is_pipe = 0;
	if ((word = get_next_word(input, i)) == NULL)
        error_exit(NULL, "malloc failed\n", c, 1);
	else if (word[0] == '\0')
		parsing_error("minishell: syntax error near unexpected token `newline'\n", parse_error, c, 258);
	else if (word[0] == '<' || word[0] == '>' || word[0] == '|')
	{
		if (input[*i] == '|')
			is_pipe = 1;
		count = count_redirections(word[0], word);
		syntax_error(word, count, is_pipe);
		parsing_error(NULL, parse_error, c, 258);
	}
}

void	handle_redirection_syntax(char *input, int *i, int *parsing_error, t_cmd_data **c)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		*i += 2;
		get_word_syntax(input, i, parsing_error, c);
	}
	else if (input[*i] == '<')
	{
		*i += 1;
		get_word_syntax(input, i, parsing_error, c);
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		*i += 2;
		get_word_syntax(input, i, parsing_error, c);
	}
	else if (input[*i] == '>')
	{
		*i += 1;
		get_word_syntax(input, i, parsing_error, c);
	}
}
// cat arg1 arg2 <Makefile arg3

void	get_words_syntax(char *input, int *i, t_cmd_data **c)
{
	char	*word;

	while (input[*i] && input[*i] != '|')
	{
		if (!(word = get_next_word(input, i)))
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

void	handle_command_syntax(char *input, int *i, t_cmd_data **c)
{
	get_words_syntax(input, i, c);
}

int	check_pipe_syntax(int *pipe, char *input, int i, t_cmd_data **c)
{
	if (*pipe == 2 || *pipe == 1)
	{
		parsing_error("minishell: syntax error near unexpected token `|'\n", NULL, c, 258);
		return (*pipe);
    }
	while (ft_isspace(input[i]))
		i++;
	if (!input[i])
	{
		parsing_error("minishell: syntax error near unexpected token `newline'\n", NULL, c, 258);
		return (1);
	}
	return (0);
}


void	syntax_check(char *input, int *syntax_error, t_cmd_data **c)
{
	int		i;
	int pipe;

	i = 0;
	pipe = 2;
	while (input[i] && !(*syntax_error))
	{
		while (ft_isspace(input[i]) == 1)
			i++;
		if (input[i] == '|')
		{
            *syntax_error = check_pipe_syntax(&pipe, input, i + 1, c);
			pipe = 1;
			i++;
			continue ;
		}
        pipe = 0;
		if (input[i] == '<' || input[i] == '>')
			handle_redirection_syntax(input, &i, syntax_error, c);
		else
			handle_command_syntax(input, &i, c);
	}
}

int	parser(t_cmd_data **c, t_cmd_env *e, char *input)
{
	int	syntax_error;

	syntax_error = 0;
	syntax_check(input, &syntax_error, c);
	if (syntax_error == 2)
	{
		free_t_cmd_env(e);
		return (0);
	}
	if (syntax_error == 1)
	{
		parse_input(c, input, e);
		free_t_cmd_env(e);
		free_t_cmd_data(c, 1);
		return (0);
	}
	else
	{
		parse_input(c, input, e);
		return (1);
	}
}
