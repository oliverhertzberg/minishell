#include "../../headers/minishell.h"

/*
	SHORT NAMES FOR VARIABLES BECAUSE OF LINES BEING TOO LONG!
	EXPLANATIONS BELOW:
	b stands for buffer.
	d stands for delmiter.
*/
static void	retrieve_heredoc(char *d, int heredoc_fd, t_cmd_data **c)
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

static void	remove_quotes(char **delimiter, t_cmd_data **c)
{
	size_t	size;
	char	*trimmed;

	size = bytes_to_malloc(*delimiter);
	trimmed = (char *)malloc(size + 1);
	if (!trimmed)
		error_exit(NULL, "malloc failed\n", c, 1);
	trim_delimiter(&trimmed, *delimiter);
	free (*delimiter);
	*delimiter = trimmed;
	(*c)->env_ptr->hdoc_expand = 0;
}

static void	get_unique_file_name(char **filename, t_cmd_data **c)
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
		if (!new_name)
			free_and_exit(string_num, *filename, c);
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

	file_name = (char *)malloc(10);
	if (!file_name)
		error_exit(NULL, "malloc failed\n", c, 1);
	ft_strlcpy(file_name, ".here_doc", 10);
	get_unique_file_name(&file_name, c);
	get_word(&delimiter, c, input, i);
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		remove_quotes(&delimiter, c);
	if ((*c)->env_ptr->parsing_error == 1)
		return (free_delim_and_filename(delimiter, file_name));
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		error_exit(NULL, "failed to open heredoc\n", c, 1);
	if ((*c)->heredoc)
		file_lstclear(&(*c)->heredoc, 1);
	file_lstadd_back(&((*c)->heredoc), file_lstnew(file_name, fd, 2));
	retrieve_heredoc(delimiter, (*c)->heredoc->fd, c);
	(*c)->is_here_doc = 1;
}