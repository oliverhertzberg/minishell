#include "../../headers/minishell.h"

static void	input_redirection(t_cmd_data **c, char *input, int *i)
{
	char	*infile;

	get_word(&infile, c, input, i);
	if ((*c)->env_ptr->parsing_error == 1)
		return ;
	file_lstadd_back(&((*c)->infile), file_lstnew(infile, -2, 0));
	if ((*c)->is_here_doc == 1)
		(*c)->is_here_doc = 0;
}

static void	output_redirection(t_cmd_data **c, char *input, int *i, int append)
{
	char	*file;

	get_word(&file, c, input, i);
	if ((*c)->env_ptr->parsing_error == 1)
		return ;
	file_lstadd_back(&((*c)->outfile), file_lstnew(file, -2, append));
}

void	handle_redirection(t_cmd_data **c, char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		*i += 2;
		here_doc(c, input, i);
	}
	else if (input[*i] == '<')
	{
		*i += 1;
		input_redirection(c, input, i);
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		*i += 2;
		output_redirection(c, input, i, 1);
	}
	else if (input[*i] == '>')
	{
		*i += 1;
		output_redirection(c, input, i, 0);
	}
}
