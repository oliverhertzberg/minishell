#include "../../headers/minishell.h"

// create universal function that will free everything allocated, whatever exists, and add it every time 
// we have some error!!!
void	error_msg(char *c, char *str)
{
	write(2, "minishell: ", 12);
	if (c)
		write(2, c, ft_strlen(c));
	if (str)
		write(2, str, ft_strlen(str));
}

void	malloc_error(void)
{
	write(2, "minishell: memoryallocation failed\n", 30);
	exit(1);
}


void	ft_puterror(int code, char *str, t_cmd_data *cmd)
{
	char	*msg;
	char	*temp;

	if ((code == 127 || code == 126) && cmd)
	{
		temp = ft_strdup(cmd->args[0]);
		if (!temp)
			malloc_error();
		msg = ft_strjoin(temp, str);
		free(temp);
	}
	else
		msg = ft_strdup(str);
	if (!msg)
		malloc_error();
	ft_putendl_fd(msg, 2);
	free(msg);
	exit(code); //will need to change the exit_code later
}

void	quote_error(void) //remove this and include it in code
{
	write(2, "minishell: quote error\n", 24);
	exit(1);
}

// item is the file or cmd that failed
// message the error message, should be NULL if perror handles the message
// error_exit will exit after
// ALSO NEED TO MAKE IT FREE HASHMAP

//error_exit(cmd, " command not found\n", c, 127);
void	error_exit(char *item, char *msg, t_cmd_data **d, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (item)
	{
		ft_putstr_fd(item, 2);
		ft_putstr_fd(": ", 2);
	}
	if (!msg)
		perror("");
	else
		ft_putstr_fd(msg, 2);
	if ((*d)->env_ptr->num_of_cmds == 1 && is_builtin(*d))
	{
		(*d)->env_ptr->exit_code = exit_code;
		free_t_cmd_env((*d)->env_ptr);
		free_t_cmd_data(d, 1);
	}
	else
	{
		free_t_cmd_env((*d)->env_ptr);
		free_t_cmd_data(d, 0);
		exit(exit_code);
	}
}

// making error function for parser, that can handle
void	parsing_error(char *item, char *msg, t_cmd_data **d, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (item)
	{
		ft_putstr_fd(item, 2);
		ft_putstr_fd(": ", 2);
	}
	if (!msg)
		perror("");
	else
		ft_putstr_fd(msg, 2);
	(*d)->env_ptr->exit_code = exit_code;
	(*d)->env_ptr->parsing_error = 1;
}


// // exit code can be found in t_cmd_env struct exit code, need to set it 
// // before calling exit function
// void	error_exit_msg(char *c, char *str, t_cmd_data **d, t_cmd_env *e)
// {
// 	error_msg(c, str);
// 	error_exit(0, d, e);
// }

// void	ft_puterror(int code, char *str, t_cmd_data *cmd)
// {
// 	char	*msg;
// 	char	*temp;

// 	if ((code == 127 || code == 126) && cmd)
// 	{
// 		temp = ft_strdup(cmd->args[0]);
// 		if (!temp)
// 			malloc_error();
// 		msg = ft_strjoin(temp, str);
// 		free(temp);
// 	}
// 	else
// 		msg = ft_strdup(str);
// 	if (!msg)
// 		malloc_error();
// 	ft_putendl_fd(msg, 2);
// 	free(msg);
// 	exit(code); //will need to change the exit_code later
// }
