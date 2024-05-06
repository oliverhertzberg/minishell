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
	struct s_file *next;
} t_file;

typedef struct	s_parser
{
	char	*string;
	int		fd_here_doc;
	t_file	*heredoc_delimiter;
	t_file	*infile;
	t_file	*outfile;
	int		append;
	int		fd_in;
	int		fd_out;
	char	*cmd_path;
	char 	**args;
	int		num_of_cmds;
	struct s_parser *next;
}	t_parser;

typedef struct s_input
{
	t_hmap		*v;
	t_parser	*input_split;
}	t_input;

/* parser_utils.c */
/*t_parser	*lstnew(char *content);
void    	lstadd_back(t_parser **lst, t_parser *new);
void		lstclear(t_parser **lst);*/

/*parser.c*/
//void    parse_string(t_parser **p);

/* split.c */
//void    split_by_pipe(t_parser **p, char *input);

#endif
