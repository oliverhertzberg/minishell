#include "../../headers/minishell.h"

static void	set_error_and_free(t_cmd_data **c, char **array, char *file)
{
	(*c)->env_ptr->parsing_error = 1;
	free(array);
	psfd ("minishell: ", 2);
	psfd (file, 2);
	psfd (": ambiguous redirect\n", 2);
	free(file);
	(*c)->env_ptr->exit_code = 1;
}

static void	input_redirection(t_cmd_data **c, char *input, int *i)
{
	char	*infile;
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * 2);
	get_word(&arr[0], c, input, i);
	if ((*c)->env_ptr->parsing_error == 1)
	{
		free (arr[0]);
		return (free (arr));
	}
	infile = ft_strdup(arr[0]);
	if (!infile)
		error_exit(infile, "malloc failed\n", c, 1);
	arr[1] = NULL;
	clean_dlr(arr, (*c)->env_ptr->hashmap, (*c)->env_ptr->exit_code);
	if (!arr[0])
		return (set_error_and_free(c, arr, infile));
	infile = ft_strdup(arr[0]);
	if (!infile)
		error_exit(infile, "malloc failed\n", c, 1);
	free (arr[0]);
	free (arr);
	file_lstadd_back(&((*c)->infile), file_lstnew(infile, -2, 0));
	if ((*c)->is_here_doc == 1)
		(*c)->is_here_doc = 0;
}

static void	output_redirection(t_cmd_data **c, char *input, int *i, int append)
{
	char	*file;
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * 2);
	get_word(&arr[0], c, input, i);
	if ((*c)->env_ptr->parsing_error == 1)
	{
		free (arr[0]);
		free (arr);
		return ;
	}
	file = ft_strdup(arr[0]);
	if (!file)
		error_exit(file, "malloc failed\n", c, 1);
	arr[1] = NULL;
	clean_dlr(arr, (*c)->env_ptr->hashmap, (*c)->env_ptr->exit_code);
	if (!arr[0])
		return (set_error_and_free(c, arr, file));
	file = ft_strdup(arr[0]);
	if (!file)
		error_exit(file, "malloc failed\n", c, 1);
	free (arr[0]);
	free (arr);
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
