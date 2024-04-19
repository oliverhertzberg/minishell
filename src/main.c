#include "../headers/minishell.h"

/*void	get_env(t_var *hashmap, char **env)
{
	if (!env)
		return ;
	ft_export();
	
}*/

int main(int argc, char **argv, char **env)
{
	char	*input;
	t_var	hashmap;

	(void)argc;
	(void)argv;
	
	//get_env(env, &hashmap);
	while (1)
	{
		input = readline("Minishell:$ ");
		ft_strip(&input);
		if (ft_strcmp(input, "pwd") == 0)
			ft_pwd();
		else if (ft_strncmp(input, "echo", 4) == 0)
			ft_echo(input);
		else
			printf("%s\n", input);
		add_history(input);
		free(input);
	}
	return (0);
}
