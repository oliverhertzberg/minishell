#include "../../headers/minishell.h"

static void	handle_redirection_syntax(char *inp, int *i, int *p, t_cmd_data **c)
{
	if (inp[*i] == '<' && inp[*i + 1] == '<')
	{
		*i += 2;
		get_word_syntax(inp, i, p, c);
	}
	else if (inp[*i] == '<')
	{
		*i += 1;
		get_word_syntax(inp, i, p, c);
	}
	else if (inp[*i] == '>' && inp[*i + 1] == '>')
	{
		*i += 2;
		get_word_syntax(inp, i, p, c);
	}
	else if (inp[*i] == '>')
	{
		*i += 1;
		get_word_syntax(inp, i, p, c);
	}
}

static void	handle_command_syntax(char *input, int *i, t_cmd_data **c)
{
	get_words_syntax(input, i, c);
}

static int	check_pipe_syntax(int *pipe, char *input, int i, t_cmd_data **c)
{
	if (*pipe == 2 || *pipe == 1)
	{
		parsing_error("minishell: syntax error near unexpected token `|'\n",
			NULL, c, 258);
		return (*pipe);
	}
	while (ft_isspace(input[i]))
		i++;
	if (!input[i])
	{
		parsing_error(
			"minishell: syntax error near unexpected token `newline'\n",
			NULL, c, 258);
		return (1);
	}
	return (0);
}

static void	syntax_check(char *input, int *syntax_error, t_cmd_data **c)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 2;
	check_unclosed_quotes(syntax_error, input, c);
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
		clear_structs(c, 1, e);
		return (0);
	}
	else
	{
		parse_input(c, input, e);
		if (e->parsing_error == 1)
			return (clear_structs(c, 1, e), 0);
		return (1);
	}
}
