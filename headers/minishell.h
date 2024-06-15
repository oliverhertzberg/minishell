#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>
# include <signal.h>
# include "builtins.h"
# include "utils.h"
# include "../libft/headers/libft.h"
# include <unistd.h>

typedef struct s_hmap	t_hmap;

# define LONG_MAX 9223372036854775807

extern int				g_sigint_received;

/* 
linked list for infiles, outfiles and heredocs
*/
typedef struct s_file
{
	char			*file;
	int				fd;
	int				append;
	struct s_file	*next;
}	t_file;

/* 
in case we get something like this:
cat <file2 -e
args should be = {"cat", -e, NULL};
with arg_lst we get a linked list of strings, that we .
*/
typedef struct s_dollar
{
	char	**str;
	t_hmap	**h;
	int		ec;
	char	*new_str;
	char	*temp;
}	t_dollar;

typedef struct s_arg_lst
{
	char				*arg;
	struct s_arg_lst	*next;
}	t_arg_lst;

typedef struct s_cmd_env
{
	char			*input;
	int				parsing_error;
	int				hdoc_expand;
	int				stdin_cpy;
	int				stdout_cpy;
	int				*pipes;
	pid_t			*pid;
	int				num_of_cmds;
	char			**paths;
	int				exit_code;
	char			**env_copy;
	char			*PWD;
	t_hmap			**hashmap;
}	t_cmd_env;

/* 
this list contains variables for the child processes 
that will execute the commands
*/
typedef struct s_cmd_data
{
	int					in_use;
	int					is_here_doc;
	t_file				*infile;
	t_file				*outfile;
	t_file				*heredoc;
	char				*cmd_path;
	t_arg_lst			*arg_lst;
	int					arg_count;
	char				**args;
	struct s_cmd_data	*next;
	struct s_cmd_env	*env_ptr;
}	t_cmd_data;

typedef struct s_input
{
	t_hmap		*v;
	t_cmd_data	*input_split;
}	t_input;

/* PARSING */

/* arg_lst.c */
t_arg_lst	*arg_lstnew(char *arg);
void		arg_lstadd_back(t_arg_lst **lst, t_arg_lst *new);
void		arg_lstclear(t_arg_lst **lst);

/* file_list_utils.c*/
t_file		*file_lstnew(char *file, int fd, int append);
void		file_lstadd_back(t_file **lst, t_file *new);
void		file_lstclear(t_file **lst, int unlink_f);

/* parser_utils.c */
t_cmd_data	*lstnew(t_cmd_env *e);
void		lstadd_back(t_cmd_data **lst, t_cmd_data *new);
void		lstclear(t_cmd_data **lst);

/* parser.c */
int			parser(t_cmd_data **c, t_cmd_env *e, char *input);
void		parse_input(t_cmd_data **c, char *input, t_cmd_env *c_env);
int			count_words(char *input, int j, t_cmd_data **c);
char		*get_next_word(char *input, int *i);
void		get_word(char **word, t_cmd_data **c, char *input, int *i);
void		here_doc(t_cmd_data **c, char *input, int *i);
void		free_and_exit(char *string_num, char *filename, t_cmd_data **c);
void		free_delim_and_filename(char *delimiter, char *filename);
size_t		bytes_to_malloc(char *delimiter);
void		trim_delimiter(char **trimmed, char *delimiter);
void		handle_command(t_cmd_data **c, char *input, int *i);
int			count_words(char *input, int j, t_cmd_data **c);
void		handle_redirection(t_cmd_data **c, char *input, int *i);
void		get_words_syntax(char *input, int *i, t_cmd_data **c);
void		get_word_syntax(char *input, int *i, int *parse_error,
				t_cmd_data **c);
int			is_next_word_redirect(char *input, int i);
void		check_unclosed_quotes(int *s_error, char *input, t_cmd_data **c);

/* init_c_env.c */
void		init_c_env(t_cmd_env *c, char **env);

/* dolar_handling.c */
void		clean_dlr(char **str, t_hmap **h, int exit_code);
char		*single_quotes(char *str, int *j);

/* dolar_handling1.c */
char		*double_quotes(char *str, int *j, t_hmap **h, char *exit_code);

/* dolar_handling2.c */
char		*no_quotes(char *str, int *j, t_hmap **h, char *exit_code);
void		handle_single_quotes(t_dollar *d, int *i, int *j);

/* dolar_handling3.c */
void		clean_dlr_hd(char **str, t_hmap **h, int exit_code);

/* dolar_handling4.c */
void		handle_dollar52(int *j, int exit_code, char **new_str);

/* EXECUTION */
/*execute_commands.c*/
void		execution(t_cmd_data **c, t_cmd_env *c_env);
void		execute_command(t_cmd_data **c, t_cmd_env *e, int cmd_index);
t_cmd_data	*pop_node_in_use(t_cmd_data **lst);
int			open_infiles(t_cmd_data **cmd);
int			open_outfiles(t_cmd_data **cmd);
void		clean_infiles(t_cmd_data **cmd);
void		clean_outfile(t_cmd_data **cmd);
char		*cmd_file_bin(char *cmd, char **paths, t_cmd_data **c);
char		*get_cmd_path(char *cmd, char **paths, t_cmd_data **c);
int			redirect_fd_in(t_cmd_data **cmd, t_cmd_env *e, int cmd_index);
int			redirect_fd_out(t_cmd_data **cmd, t_cmd_env *e, int cmd_index);
void		malloc_and_create_pipes(t_cmd_env *e, t_cmd_data **c);
void		reset_stdio(t_cmd_env *e);

/* execution_utils.c*/
t_cmd_data	*pop_node_in_use(t_cmd_data **lst);
void		free_t_cmd_data(t_cmd_data **d, int rm_hdoc);
void		free_t_cmd_env(t_cmd_env *e);
void		clear_structs(t_cmd_data **d, int rm_hdoc, t_cmd_env *e);
void		clear_pipes(t_cmd_env *e);
void    	free_args(char **args, int arg_count);

/* controls*/
void		rl_replace_line(const char *text, int clear_undo);
void		rl_redisplay(void);
void		set_signals(void);
void		set_heredoc_signals(void);
void		caret_switch(int on);
void		set_signals_from_parent(void);
void		sigquit_handler(int signum);
void		sigint_handler_2(int signum);
void		heredoc_sigint(int signum);
void		ctrl_d_handler(char *str, t_cmd_data **p);
void		sigint_handler(int signum);
void		reset_signals(void);

#endif
