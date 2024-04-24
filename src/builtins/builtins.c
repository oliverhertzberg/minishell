#include "../../headers/builtins.h"

// add arguments to functions when they are done!
void  do_builtins(char *line, int *i, t_builtins *b)
{
	t_env	*path;

	path = getcwd(); //not quite sure
  if (ft_strcmp(b->name, "echo") == 0)
    ft_echo();
  else if (ft_strcmp(b->name, "cd") == 0)
    ft_cd(line, path);
  else if (ft_strcmp(b->name, "pwd") == 0)
    ft_pwd();
  else if (ft_strcmp(b->name, "export") == 0)
    ft_export();
  else if (ft_strcmp(b->name, "unset") == 0)
    ft_unset();
  else if (ft_strcmp(b->name, "env") == 0)
    ft_env();
  else if (ft_strcmp(b->name, "exit") == 0)
    ft_exit();
  else
    return ;
}

t_builtins  create_builtins(char **line) //sending pointer to a string so that we can change it in the memory, check this!
{
  t_builtins  b;
  int  i;
  
  ft_strip(line);
  if (!line)
    return (NULL);
  i = 0;
  while (*line[i] != 0 && ft_isspace(*line[i]) == 0)
    i++;
  b.name = malloc(i + 1);
// malloc error
  i = 0;
  //taking builtins name and putting into struct
  while (*line[i] != 0 && ft_isspace(*line[i]) == 0)
    {
      b.name[i] = *line[i];
      i++;
    }
  do_builtins(&line, &i);
  return (b);
}
