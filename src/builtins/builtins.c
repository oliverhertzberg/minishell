#include "../../headers/builtins.h"

// add arguments to functions when they are done!
void  do_builtins(t_cmd_data *d, t_cmd_env e, int *return_value)
{
	t_hmap	*path;

  *return_value = 1;
  if (ft_strcmp(d->args[0], "echo") == 0)
    ft_echo();
  else if (ft_strcmp(d->args[0], "cd") == 0)
    ft_cd();
  else if (ft_strcmp(d->args[0], "pwd") == 0)
    ft_pwd();
  else if (ft_strcmp(d->args[0], "export") == 0)
    ft_export();
  else if (ft_strcmp(d->args[0], "unset") == 0)
    ft_unset();
  else if (ft_strcmp(d->args[0], "env") == 0)
    ft_env();
  else if (ft_strcmp(d->args[0], "exit") == 0)
    ft_exit();
  else
    *return_value = 0;
}

// function for dealing with quotes and cleaning builtings from it
int  check_builtins(t_cmd_data **d)
{

}

int is_builting(t_cmd_data *data, t_cmd_env e) // test this
{
  if (check_word(data->args[0], 0, ft_strlen(data->args[0])) == 2)
    ft_skip(data->args[0]);
  if (check_word(data->args[0], 0, ft_strlen(data->args[0])) == 3)
  {
    if (ft_strcmp(data->args[0], "echo") == 0
      || ft_strcmp(data->args[0], "cd") == 0
      || ft_strcmp(data->args[0], "pwd") == 0
      || ft_strcmp(data->args[0], "export") == 0
      || ft_strcmp(data->args[0], "unset") == 0
      || ft_strcmp(data->args[0], "env") == 0
      || ft_strcmp(data->args[0], "exit") == 0)
      return (1);
  }
  return (0);
}
