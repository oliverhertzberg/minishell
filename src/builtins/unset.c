#include "../../headers/builtins.h"

static int	unset_error(char *arg)
{
	ft_putstr_fd("minishell 🐢: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (0);
}

/* it needs to work for: unset  key.
 * u need to skip unset and all white spaces after it, and save key
 * into some string. then check if u have that key in v, and if u do
 * just remove it using function remove_var, if not do nothing */
void	ft_unset(char *input, t_hmap **v)
{
	while (ft_isspace(input[*i]) == 1)
    *i++;
//   if (input[*i] == 0)
//   //error

}
