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

void	retrieve_heredoc(char *delimiter, int heredoc_fd)
{
	char	*buf;

	while (1)
	{
		write(1, ">", 2);
		buf = get_next_line(0);
		if (!buf)
			break ;
		if (buf < 0)
			exit (1);
            // error
		if ((ft_strncmp(buf, delimiter, ft_strlen(delimiter)) == 0) \
			&& buf[ft_strlen(delimiter)] == '\n')
			break ;
		write (heredoc_fd, buf, ft_strlen(buf));
		free (buf);
	}
	if (buf)
		free (buf);
}

void	get_unique_file_name(char **filename, t_cmd_data **c)
{
	static int	file_num = 0;
	char		*new_name;
	char		*string_num;

	if (!(string_num = ft_itoa(file_num)))
		error_exit(NULL, "malloc failed\n", c, 1);
	if (!(new_name = ft_strjoin(*filename, string_num)))
		error_exit(NULL, "malloc failed\n", c, 1);
	while (access(new_name, F_OK) == 0)
	{
		free (string_num);
		free (new_name);
		file_num++;
		string_num = ft_itoa(file_num);
		if(!(new_name = ft_strjoin(*filename, string_num)))
		{
			free(string_num);
			free(*filename);
			error_exit(NULL, "malloc failed\n", c, 1);
		}
	}
	free (*filename);
	free (string_num);
	*filename = new_name;
	file_num++;
}
int	count_redirections(char redir, char *word)
{
	int i;

	i = 0;
	while (word[i] && word[i] == redir)
		i++;
	return (i);
}

void	syntax_error_redir(char *word, int count, t_cmd_data **c, int is_pipe)
{
	if (word[0] == '<')
	{
		if (count == 1)
			parsing_error(NULL, "syntax error near unexpected token `<'\n", c, 258);
		else if (count == 2)
			parsing_error(NULL, "syntax error near unexpected token `<<'\n", c, 258);
		else if (count >= 3)
			parsing_error(NULL, "syntax error near unexpected token `<<<'\n", c, 258);
	}
	else if (word[0] == '>')
	{
		if (count == 1 && is_pipe)
			parsing_error(NULL, "syntax error near unexpected token `>|'\n", c, 258);
		else if (count == 1)
			parsing_error(NULL, "syntax error near unexpected token `>'\n", c, 258);
		else if (count >= 2)
			parsing_error(NULL, "syntax error near unexpected token `>>'\n", c, 258);
	}
}

void	syntax_error_special(char *word, int count, t_cmd_data **c, int is_pipe)
{
	if (word[0] == '|')
	{
		if (count == 1 && !is_pipe)
			parsing_error(NULL, "syntax error near unexpected token `|'\n", c, 258);
		else
			parsing_error(NULL, "syntax error near unexpected token `||'\n", c, 258);
	}
	else if (word[0] == '&')
	{
		if (count == 1)
			parsing_error(NULL, "syntax error near unexpected token `&'\n", c, 258);
		else if (count >= 2)
			parsing_error(NULL, "syntax error near unexpected token `&&'\n", c, 258);
	}
}

void	get_word(char **word, t_cmd_data **c, char *input, int *i)
{
	int count;
	int	is_pipe;

	is_pipe = 0;
	count = 0;
	if ((*word = get_next_word(input, i)) == NULL)
		parsing_error(NULL, "malloc failed\n", c, 1);
	else if ((*word)[0] == '\0')
		parsing_error(NULL, "syntax error near unexpected token `newline'\n", c, 258);
	else if ((*word)[0] == '<' || (*word)[0] == '>')
	{
		if (input[*i] == '|')
			is_pipe = 1;
		count = count_redirections((*word)[0], *word);
		syntax_error_redir(*word, count, c, is_pipe);
	}
	else if ((*word)[0] == '&' || (*word)[0] == '|')
	{
		if (input[*i] && input[*i + 1] == '|')
			is_pipe = 1;
		count = count_redirections((*word)[0], *word);
		syntax_error_special(*word, count, c, is_pipe);
	}
}

void	here_doc(t_cmd_data **c, char *input, int *i)
{
	char	*delimiter;
	char	*file_name = "XD";
	int		fd;

	if (!(file_name = (char *)malloc(10)))
		error_exit(NULL, "malloc failed\n", c, 1);
	ft_strlcpy(file_name, ".here_doc", 10);
	//get_unique_file_name(&file_name, c);
	get_word(&delimiter, c, input, i); //free delim here, if this fails, c->env_ptr->syntax_error ==1 and break ;
	if ((*c)->env_ptr->parsing_error == 1)
	{
		free (delimiter);
		free(file_name);
		return ;
	}
	if ((fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
		parsing_error(NULL, "failed to open heredoc\n", c, 1);
	if ((*c)->heredoc)
		file_lstclear(&(*c)->heredoc, 1);
	file_lstadd_back(&((*c)->heredoc), file_lstnew(file_name, fd, 2));
	retrieve_heredoc(delimiter, (*c)->heredoc->fd);
	(*c)->is_here_doc = 1;
}

void	input_redirection(t_cmd_data **c, char *input, int *i)
{
	char	*infile;

	get_word(&infile, c, input, i); //if syntax error return
	file_lstadd_back(&((*c)->infile), file_lstnew(infile, -2, 0));
	if ((*c)->is_here_doc == 1)
		(*c)->is_here_doc = 0;
}

void	output_redirection(t_cmd_data **c, char *input, int *i, int append)
{
	char	*file;

	get_word(&file, c, input, i); // if syntax error return
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

static int	count_words(char *input, int j)
{
	char	*word;
	int		count;
	int		i;

	i = j;
	count = 0;
	while (input[i] && input[i] != '|')
	{
		word = get_next_word(input, &i);
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

void	handle_command(t_cmd_data **c, char *input, int *i)
{
	int	word_count;
	int	j;

	word_count = count_words(input, *i);
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


/*
t_file				*infile;
	t_file				*outfile;
	t_file				*heredoc;
	char				*cmd_path;
	t_arg_lst			*arg_lst;
	int					arg_count;
*/
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
	(*c)->args = (char **)malloc(sizeof(char *) * ((*c)->arg_count + 1));
    // malloc error
	current = (*c)->arg_lst;
	i = -1;
	while((++i < (*c)->arg_count) && current)
	{
		(*c)->args[i] = current->arg;
		current = current->next;
	}
	(*c)->args[i] = NULL;
	if ((*c)->args[0])
	{
		init_quote(c);
		clean_quotes(c);
	}
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
