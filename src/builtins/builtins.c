#include "../../headers/builtins.h"

//add arguments to functions when they are done!
void  do_builtins(t_cmd_data *d, t_cmd_env *e)
{
  if (ft_strcmp(d->args[0], "cd") == 0)
    ft_cd(d, e->hashmap);
  if (ft_strcmp(d->args[0], "pwd") == 0)
    ft_pwd();
  if (ft_strcmp(d->args[0], "export") == 0)
    ft_export(d, e->hashmap);
  if (ft_strcmp(d->args[0], "unset") == 0)
    ft_unset(d, e->hashmap);
  if (ft_strcmp(d->args[0], "env") == 0)
    ft_env(*e->hashmap, 1);
  if (ft_strcmp(d->args[0], "exit") == 0)
    ft_exit(&d, *e);
}

 int is_builtin(t_cmd_data *data)
 {
    if(!data->args || !data->args[0])
        return (0);
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