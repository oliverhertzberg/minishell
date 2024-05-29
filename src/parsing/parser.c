#include "../../headers/minishell.h"

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

/*
	SHORT NAMES FOR VARIABLES BECAUSE OF LINES BEING TOO LONG!
	EXPLANATIONS BELOW:
	b stands for buffer.
	d stands for delmiter.
*/
void	retrieve_heredoc(char *d, int heredoc_fd, t_cmd_data **c)
{
	char	*b;
	int		backup;

	backup = dup(STDIN_FILENO);
	set_heredoc_signals();
	while (1)
	{
		write(1, ">", 2);
		b = get_next_line(0);
		if (!b)
			break ;
		if (b < 0)
			error_exit(NULL, "get_next_line failed\n", c, 1);
		if ((ft_strncmp(b, d, ft_strlen(d)) == 0) && b[ft_strlen(d)] == '\n')
			break ;
		if ((*c)->env_ptr->hdoc_expand)
			clean_dlr_hd(&b, (*c)->env_ptr->hashmap, (*c)->env_ptr->exit_code);
		write (heredoc_fd, b, ft_strlen(b));
		free (b);
	}
	if (b)
		free (b);
	dup2(backup, STDIN_FILENO);
	close(backup);
	set_signals();
}

void	free_and_exit(char *string_num, char *filename, t_cmd_data **c)
{
	free(string_num);
	free(filename);
	error_exit(NULL, "malloc failed\n", c, 1);
}

void	get_unique_file_name(char **filename, t_cmd_data **c)
{
	static int	file_num = 0;
	char		*new_name;
	char		*string_num;

	string_num = ft_itoa(file_num);
	if (!string_num)
		error_exit(NULL, "malloc failed\n", c, 1);
	new_name = ft_strjoin(*filename, string_num);
	if (!new_name)
		error_exit(NULL, "malloc failed\n", c, 1);
	while (access(new_name, F_OK) == 0)
	{
		free (string_num);
		free (new_name);
		file_num++;
		string_num = ft_itoa(file_num);
		new_name = ft_strjoin(*filename, string_num);
		if (!(new_name = ft_strjoin(*filename, string_num)))
			free_and_exit(string_num, *filename, c);
	}
	free (*filename);
	free (string_num);
	*filename = new_name;
	file_num++;
}

void	get_word(char **word, t_cmd_data **c, char *input, int *i)
{
	if ((*word = get_next_word(input, i)) == NULL)
		error_exit(NULL, "malloc failed\n", c, 1);
	else if ((*word)[0] == '\0')
		(*c)->env_ptr->parsing_error = 1;
	else if ((*word)[0] == '<' || (*word)[0] == '>')
		(*c)->env_ptr->parsing_error = 1;
	else if ((*word)[0] == '&' || (*word)[0] == '|')
		(*c)->env_ptr->parsing_error = 1;
}

size_t	bytes_to_malloc(char *delimiter)
{
	int		i;
	size_t	bytes;
	char	quote;

	quote = '\0';
	bytes = 0;
	i = -1;
	while (delimiter[++i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
		{
			if (!quote)
				quote = delimiter[i];
			else if (quote == delimiter[i])
				quote = '\0';
			else
				bytes++;
		}
		else
			bytes++;
	}
	return (bytes);
}

void	trim_delimiter(char **trimmed, char *delimiter)
{
	char	quote;
	int		i;
	int		j;

	quote = '\0';
	i = -1;
	j = 0;
	while (delimiter[++i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
		{
			if (!quote)
				quote = delimiter[i];
			else if (quote == delimiter[i])
				quote = '\0';
			else
				(*trimmed)[j++] = delimiter[i];
		}
		else
			(*trimmed)[j++] = delimiter[i];
	}
	(*trimmed)[j] = '\0';
}

void	remove_quotes(char **delimiter, t_cmd_data **c)
{
	size_t	size;
	char	*trimmed;

	size = bytes_to_malloc(*delimiter);
	if (!(trimmed = (char *)malloc(size + 1)))
		error_exit(NULL, "malloc failed\n", c, 1);
	trim_delimiter(&trimmed, *delimiter);
	free (*delimiter);
	*delimiter = trimmed;
	(*c)->env_ptr->hdoc_expand = 0;
}

void	here_doc(t_cmd_data **c, char *input, int *i)
{
	char	*delimiter;
	char	*file_name;
	int		fd;

	if (!(file_name = (char *)malloc(10)))
		error_exit(NULL, "malloc failed\n", c, 1);
	ft_strlcpy(file_name, ".here_doc", 10);
	get_unique_file_name(&file_name, c);
	get_word(&delimiter, c, input, i);
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		remove_quotes(&delimiter, c);
	if ((*c)->env_ptr->parsing_error == 1)
	{
		free (delimiter);
		free(file_name);
		return ;
	}
	if ((fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
		error_exit(NULL, "failed to open heredoc\n", c, 1);
	if ((*c)->heredoc)
		file_lstclear(&(*c)->heredoc, 1);
	file_lstadd_back(&((*c)->heredoc), file_lstnew(file_name, fd, 2));
	retrieve_heredoc(delimiter, (*c)->heredoc->fd, c);
	(*c)->is_here_doc = 1;
}

void	input_redirection(t_cmd_data **c, char *input, int *i)
{
	char	*infile;

	get_word(&infile, c, input, i);
	if ((*c)->env_ptr->parsing_error == 1)
		return ;
	file_lstadd_back(&((*c)->infile), file_lstnew(infile, -2, 0));
	if ((*c)->is_here_doc == 1)
		(*c)->is_here_doc = 0;
}

void	output_redirection(t_cmd_data **c, char *input, int *i, int append)
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

int	count_words(char *input, int j, t_cmd_data **c)
{
	char	*word;
	int		count;
	int		i;

	i = j;
	count = 0;
	while (input[i] && input[i] != '|')
	{
		if (!(word = get_next_word(input, &i)))
			error_exit(NULL, "malloc failed \n", c, 1);
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

void	handle_command(t_cmd_data **c, char *input, int *i)
{
	int	word_count;
	int	j;

	word_count = count_words(input, *i, c);
	(*c)->arg_count += word_count;
	j = -1;
	while (++j < word_count)
		arg_lstadd_back(&(*c)->arg_lst, arg_lstnew(get_next_word(input, i)));
}

void	create_new_node(t_cmd_data **p, t_cmd_data **current, t_cmd_env *env)
{
	lstadd_back(p, lstnew(env));
	env->num_of_cmds++;
	*current = (*current)->next;
}

int	struct_empty(t_cmd_data **c)
{
	if ((*c)->outfile || (*c)->heredoc || (*c)->infile || (*c)->arg_count > 0)
		return (0);
	return (1);
}

void	create_args_array(t_cmd_data **c)
{
	t_arg_lst	*current;
	int			i;

	if ((*c)->env_ptr->parsing_error == 1)
		return ;
	if (struct_empty(c))
	{
		(*c)->env_ptr->parsing_error = 1;
		return ;
	}
	if (!((*c)->args = (char **)malloc(sizeof(char *) * ((*c)->arg_count + 1))))
		error_exit(NULL, "malloc failed\n", c, 1);
	current = (*c)->arg_lst;
	i = -1;
	while ((++i < (*c)->arg_count) && current)
	{
		(*c)->args[i] = current->arg;
		current = current->next;
	}
	(*c)->args[i] = NULL;
	if ((*c)->args[0])
		clean_dolar((*c)->args, (*c)->env_ptr->hashmap, (*c)->env_ptr->exit_code);
	arg_lstclear(&(*c)->arg_lst);
}

//       <Makefile cat -e | wc -l
// need to check here if c_env->syntax_error is 1
void	parse_input(t_cmd_data **c, char *input, t_cmd_env *c_env)
{
	t_cmd_data	*current;
	int			i;

	current = *c;
	i = 0;
	while (input[i] && !c_env->parsing_error)
	{
		if (i > 0)
			create_new_node(c, &current, c_env);
		while (input[i] && !c_env->parsing_error)
		{
			while (ft_isspace(input[i]) == 1)
				i++;
			if (input[i] == '|')
			{
				i++;
				break ;
			}
			if (input[i] == '<' || input[i] == '>')
				handle_redirection(&current, input, &i);
			else
				handle_command(&current, input, &i);
		}
		create_args_array(&current);
	}
}
