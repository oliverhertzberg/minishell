#include "../../headers/minishell.h"

int	open_infiles(t_cmd_data **cmd)
{
	t_file	*last;

	last = NULL;
	while ((*cmd)->infile)
	{
		if (last)
		{
			close(last->fd);
			free(last->file);
			free(last);
		}
		last = (*cmd)->infile;
		(*cmd)->infile->fd = open((*cmd)->infile->file, O_RDONLY);
		if ((*cmd)->infile->fd < 0)
			return (error_exit((*cmd)->infile->file, NULL, cmd, 1), 0);
		(*cmd)->infile = (*cmd)->infile->next;
	}
	return ((*cmd)->infile = last, 1);
}

static void	remove_last(t_file *last)
{
	close(last->fd);
	free(last->file);
	free(last);
}

int	open_outfiles(t_cmd_data **cmd)
{
	t_file	*last;

	last = NULL;
	while ((*cmd)->outfile)
	{
		if (last)
			remove_last(last);
		last = (*cmd)->outfile;
		if ((*cmd)->outfile->append == 1)
		{
			(*cmd)->outfile->fd = open((*cmd)->outfile->file, O_APPEND
					| O_CREAT | O_RDWR, 0644) == -1;
			if ((*cmd)->outfile->fd == -1)
				return (error_exit((*cmd)->outfile->file, NULL, cmd, 1), 0);
		}
		else if ((*cmd)->outfile->append == 0)
		{
			(*cmd)->outfile->fd = open((*cmd)->outfile->file, O_TRUNC
					| O_CREAT | O_RDWR, 0644);
			if ((*cmd)->outfile->fd == -1)
				return (error_exit((*cmd)->outfile->file, NULL, cmd, 1), 0);
		}
		(*cmd)->outfile = (*cmd)->outfile->next;
	}
	return ((*cmd)->outfile = last, 1);
}

void	clean_infiles(t_cmd_data **cmd)
{
	if ((*cmd)->heredoc)
	{
		close((*cmd)->heredoc->fd);
		free((*cmd)->heredoc->file);
		free((*cmd)->heredoc);
		(*cmd)->heredoc = NULL;
	}
	if ((*cmd)->infile)
	{
		close((*cmd)->infile->fd);
		free((*cmd)->infile->file);
		free((*cmd)->infile);
		(*cmd)->infile = NULL;
	}
}

void	clean_outfile(t_cmd_data **cmd)
{
	if ((*cmd)->outfile)
	{
		close((*cmd)->outfile->fd);
		free((*cmd)->outfile->file);
		free((*cmd)->outfile);
		(*cmd)->outfile = NULL;
	}
}
