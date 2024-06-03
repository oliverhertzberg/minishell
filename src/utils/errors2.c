#include "../../headers/minishell.h"

// write(1, "syntax error near unexpected token `newline'\n", 46);
// parsing_error(NULL, "syntax error near unexpected token `newline'\n", c, 258);
// this is the function that is used when there is some issue with syntax
// it prints the error, changes the parse_error variable to 1 to indicate found error
// and sets exit code to 258, didn't hard code 258 in case there is some case with different code
// after the error unless it is at the start, we parse the string and get all heredocs before
// error, after it skips the execution
void	parsing_error(char *msg, int *parseerror, t_cmd_data **d, int exit_code)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (parseerror)
		*parseerror = 1;
	(*d)->env_ptr->exit_code = exit_code;
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

void	cd_error(t_cmd_data *cmd, char *str)
{
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putstr_fd(str, 2);
}
