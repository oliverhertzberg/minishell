#include "../../headers/builtins.h"

/* using those functions from var_utils to actually make export work 
 * properly. take key and value from input and put it inside of some strings,
 * then check if key exists, if it does, if u have value, free old one and 
 * save new one using change_value, if u have only key, don't do anything.
 * if key doesn't exist, add it inside of v.
 * */
void	ft_export(char *input, t_builtins *b, int *i)
{
  while (ft_isspace(input[*i]) == 1)
    *i++;
  if (input[*i] == 0)
    ft_env(); // make this function
}

/* it needs to work for: unset  key.
 * u need to skip unset and all white spaces after it, and save key
 * into some string. then check if u have that key in v, and if u do
 * just remove it using function remove_var, if not do nothing */
void	ft_unset(char *input, t_var **v)
{

}
