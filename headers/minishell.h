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

# define LONG_MAX 9223372036854775807

// linked list for infiles, outfiles and heredocs
typedef struct s_file
{
	char *file;
	int fd;
	int append;
	struct s_file *next;
} t_file;

// in case we get something like this:
// cat <file2 -e
// args should be = {"cat", -e, NULL};
// with arg_lst we get a linked list of strings, that we .
typedef struct s_arg_lst
{
	char	*arg;
	struct s_arg_lst *next;
}	t_arg_lst;

// this list contains variables for the child processes that will execute the commands
typedef struct	s_cmd_data
{
	int		in_use;
	int		is_here_doc;
	t_file	*infile;
	t_file	*outfile;
	t_file	*heredoc;
	char	*cmd_path;
	t_arg_lst *arg_lst;
	int		arg_count;
	char 	**args;
	struct s_cmd_data *next;
}	t_cmd_data;

typedef struct s_cmd_env
{
	int 	*pipes;
	pid_t	*pid;
	int		num_of_cmds;
	char	**paths;
	int 	exit_code;
	char **env_copy;
	t_hmap **hashmap;
}	t_cmd_env;

typedef struct s_input
{
	t_hmap		*v;
	t_cmd_data	*input_split;
}	t_input;

/* PARSING */

/* arg_lst.c */
t_arg_lst	*arg_lstnew(char *arg);
void    arg_lstadd_back(t_arg_lst **lst, t_arg_lst *new);
void	arg_lstclear(t_arg_lst **lst, int free_arg);

/* file_list_utils.c*/
t_file	*file_lstnew(char *file, int fd, int append);
void    file_lstadd_back(t_file **lst, t_file *new);
void	file_lstclear(t_file **lst);

/* parser_utils.c */
t_cmd_data	*lstnew(void);
void    	lstadd_back(t_cmd_data **lst, t_cmd_data *new);
void		lstclear(t_cmd_data **lst);

/* parser.c */
void    parse_input(t_cmd_data **c, char *input, t_cmd_env *c_env);

/* split.c */
//void    split_by_pipe(t_cmd_data **p, char *input);

/* init_c_env.c */
void init_c_env(t_cmd_env *c, char **env);

/* EXECUTION */
/*execute_commands.c*/
void    execution(t_cmd_data **c, t_cmd_env *c_env);
t_cmd_data *pop_node_in_use(t_cmd_data **lst);


/* execution_utils.c*/
t_cmd_data *get_node_in_use(t_cmd_data **lst);
void    	cleanup_resources_child(t_cmd_data *data, t_cmd_env *env);
void		free_t_cmd_data(t_cmd_data **d);
void		free_t_cmd_env(t_cmd_env *e);
void		clear_pipes(t_cmd_env *e);
#endif
