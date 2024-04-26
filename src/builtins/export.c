#include "../../headers/builtins.h"

/* using those functions from var_utils to actually make export work 
 * properly. take key and value from input and put it inside of some strings,
 * then check if key exists, if it does, if u have value, free old one and 
 * save new one using change_value, if u have only key, don't do anything.
 * if key doesn't exist, add it inside of v.
 * */
void	ft_export(char *input, t_builtins *b, int *i)
{
  char  *key;
  char  *value;

  while (ft_isspace(input[*i]) == 1)
    *i++;
  if (input[*i] == 0)
  {
    ft_env(); //check if we need to sort it or whatever
    return ;
  }
  while (input[*i] != 0)
    {
      key = take_key(input, i);
      value = take_value(input, i);
      if (!key && value)
        // error & free value
      else if (key && !value)
      {
        add_new_var(b->v, key, NULL); //check it
        free(key);
      }
      else if (key && value)
      {
        if (key_exists(b->v, key) == 1)
          change_value(b->v, key, value); // check this
        else
          add_new_var(b->v, key, value);
        free(key);
        free(value);
      }
      else
        //error or whatever
      
      *i++;
    }
}