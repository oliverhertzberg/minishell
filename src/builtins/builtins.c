#include "../../headers/builtins.h"

t_builtins  create_builtins(char **line) //sending pointer to a string so that we can change it in the memory
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
  i = 0;
  //taking builtins name and putting into struct
  while (*line[i] != 0 && ft_isspace(*line[i]) == 0)
    {
      b.name[i] = *line[i];
      i++;
    }
  do_builtins(); //create this based on different builtins what should happen
  return (b);
}
