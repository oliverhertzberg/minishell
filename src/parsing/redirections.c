#include "../../headers/minishell.h"

static void	input_redirection(t_cmd_data **c, char *input, int *i)
{
	char	*infile;
	char	**clean_dlr_array;

	clean_dlr_array = (char **)malloc(sizeof(char *) * 2);
	get_word(&clean_dlr_array[0], c, input, i);
	if ((*c)->env_ptr->parsing_error == 1)
	{
		free (clean_dlr_array[0]);
		free (clean_dlr_array);
		return ;
	}
	clean_dlr_array[1] = NULL;
	clean_dlr(clean_dlr_array, (*c)->env_ptr->hashmap, (*c)->env_ptr->exit_code);
	infile = ft_strdup(clean_dlr_array[0]);
	if (!infile)
		error_exit(NULL, "Malloc failed\n", c, 1);
	free (clean_dlr_array[0]);
	free (clean_dlr_array);
	file_lstadd_back(&((*c)->infile), file_lstnew(infile, -2, 0));
	if ((*c)->is_here_doc == 1)
		(*c)->is_here_doc = 0;
}

static void	output_redirection(t_cmd_data **c, char *input, int *i, int append)
{
	char	*file;
	char	**clean_dlr_array;


	clean_dlr_array = (char **)malloc(sizeof(char *) * 2);
	get_word(&clean_dlr_array[0], c, input, i);
	if ((*c)->env_ptr->parsing_error == 1)
	{
		free (clean_dlr_array[0]);
		free (clean_dlr_array);
		return ;
	}
	clean_dlr_array[1] = NULL;
	clean_dlr(clean_dlr_array, (*c)->env_ptr->hashmap, (*c)->env_ptr->exit_code);
	file = ft_strdup(clean_dlr_array[0]);
	if (!file)
		error_exit(NULL, "Malloc failed\n", c, 1);
	free (clean_dlr_array[0]);
	free (clean_dlr_array);
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
