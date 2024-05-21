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
		if ((ft_strncmp(buf, delimiter, ft_strlen(delimiter)) == 0)
			&& buf[ft_strlen(delimiter)] == '\n')
			break ;
		write (heredoc_fd, buf, ft_strlen(buf));
		free (buf);
	}
	if (buf)
		free (buf);
}

void	get_unique_file_name(char **filename)
{
	static int	file_num = 0;
	char		*new_name;
	char		*string_num;

	string_num = ft_itoa(file_num);
    // malloc error
	new_name = ft_strjoin(*filename, string_num);
    // malloc error
	while (access(new_name, F_OK) == 0)
	{
		free (string_num);
		free (new_name);
		file_num++;
		string_num = ft_itoa(file_num);
        // malloc error
		new_name = ft_strjoin(*filename, string_num);
        // malloc error
	}
	free (*filename);
	free (string_num);
	*filename = new_name;
	file_num++;
}

void	here_doc(t_cmd_data **c, char *input, int *i)
{
	char	*delimiter;
	char	*file_name;
	int		fd;

	*i += 2;
	file_name = (char *)malloc(10);
	ft_strlcpy(file_name, ".here_doc", 10);
	get_unique_file_name(&file_name);
	if ((delimiter = get_next_word(input, i)) == NULL)
		exit(1);
        // malloc error
	if ((fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
		exit(1);
        // open error
	if ((*c)->heredoc)
	{
		unlink((*c)->heredoc->file);
		free((*c)->heredoc);
		(*c)->heredoc = NULL;
	}
	file_lstadd_back(&((*c)->heredoc), file_lstnew(file_name, fd, 2));
	retrieve_heredoc(delimiter, (*c)->heredoc->fd);
	if ((*c)->is_here_doc == 0)
		(*c)->is_here_doc = 1;
}

void	input_redirection(t_cmd_data **c, char *input, int *i)
{
	char	*infile;

	*i += 1;
	if ((infile = get_next_word(input, i)) == NULL)
		exit (1);
        // malloc error
	file_lstadd_back(&((*c)->infile), file_lstnew(infile, -2, 0));
	if ((*c)->is_here_doc == 1)
		(*c)->is_here_doc = 0;
}

void	output_redirection(t_cmd_data **c, char *string, int *i, int append)
{
	char	*file;

	if (append == 0)
		(*i)++;
	else if (append == 1)
		(*i) += 2;
	if ((file = get_next_word(string, i)) == NULL)
		exit (1);
        // malloc error
	file_lstadd_back(&((*c)->outfile), file_lstnew(file, -2, append));
}

void	handle_redirection(t_cmd_data **c, char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
		here_doc(c, input, i);
	else if (input[*i] == '<')
		input_redirection(c, input, i);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		output_redirection(c, input, i, 1);
	else if (input[*i] == '>')
		output_redirection(c, input, i, 0);
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
		if (word[0] == '<' || word[0] == '>' || word[0] == '|' \
			|| word[0] == '\0')
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

void	create_new_node(t_cmd_data **p, t_cmd_data **current, t_cmd_env *c_env)
{
	lstadd_back(p, lstnew());
	c_env->num_of_cmds++;
	*current = (*current)->next;       
}

void	create_args_array(t_cmd_data **c)
{
	t_arg_lst	*current;
	int			i;

	(*c)->args = (char **)malloc(sizeof(char *) * ((*c)->arg_count + 1));
    // malloc error
	current = (*c)->arg_lst;
	i = -1;
	while ((++i < (*c)->arg_count) && current)
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
void	parse_input(t_cmd_data **c, char *input, t_cmd_env *c_env)
{
	t_cmd_data	*current;
	int			i;

	current = *c;
	i = 0;
	while (input[i])
	{
		if (i > 0)
			create_new_node(c, &current, c_env);
		while (input[i])
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
