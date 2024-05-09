#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h> // readline
# include <readline/history.h> // add_history
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free, exit, getenv
# include <fcntl.h> // open

# include "builtins.h"
# include "utils.h"
# include "../libft/libft.h"

typedef struct s_hmap t_hmap; // this shouldn't be needed because the whole header is included

typedef struct s_file
{
	char *file;
	int fd;
	int append;
	struct s_file *next;
} t_file;

typedef struct	s_cmd_data
{
	int		is_here_doc;
	t_file	*heredoc;
	t_file	*infile;
	t_file	*outfile;
	int		append;
	int		fd_in;
	int		fd_out;
	char	*cmd_path;
	char 	**args;
	struct s_cmd_data *next;
}	t_cmd_data;

typedef struct s_cmd_env
{
	int 	*pipes;
	int		num_of_cmds;
	char	**paths;
}	t_cmd_env;

typedef struct s_input
{
	t_hmap		*v;
	t_cmd_data	*input_split;
}	t_input;


/* PARSING */
/* file_list_utils.c*/
t_file	*file_lstnew(char *file, int fd, int append);
void    file_lstadd_back(t_file **lst, t_file *new);
void	file_lstclear(t_file **lst);

/* parser_utils.c */
t_parser	*lstnew(void);
void    	lstadd_back(t_cmd_data **lst, t_cmd_data *new);
void		lstclear(t_cmd_data **lst);
void		free_t_parser(t_cmd_data **p);

/* parser.c */
void    parse_input(t_cmd_data **p, char *input);

/* split.c */
void    split_by_pipe(t_cmd_data **p, char *input);


/* EXECUTION */
/*execute_commands.c*/
void    execute_commands(t_cmd_data **p);

#endif
