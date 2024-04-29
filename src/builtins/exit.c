#include "../../headers/builtins.h"

// check for overflows long max, min
static void free_input(char **input)
{
  int i;

  i = 0;
  while (input[i] != NULL)
  {
    free(input[i]);
    i++;
  }
  free(input);
}

static int is_num(char *str)
{
  int i;

  i = 0;
  while (str[i] != '\0')
  {
    if(ft_isdigit(str[i]) == 0)
      return (0);
    i++;
  }
  return (1);
}

static void get_exit_code(char **input)
{
  int code;

  code = 0;
  if(is_num(str[1]) == 0)
    code = ft_atoi(input[1]);
  else
  {
	  ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	  ft_putstr_fd(str[1], STDERR_FILENO);
	  ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	  exit_code = 255;
  }
  free_input(input);
  exit(code);
}

void ft_exit(t_hmap **env, char *input)
{
	char **args;
	ft_putstr_fd("Exiting minishell...\n", STDERR_FILENO);
	if (input[1] && input[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	args = special_split(input);
	get_exit_code(args);
	free_env_and_all(t_stack env); // need to get this, free function for all
	exit(0);
}
