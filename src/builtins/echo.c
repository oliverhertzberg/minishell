#include "../../headers/builtins.h"

/* we should change it to work with export and unset also!
 * this is doing the simpest stuff, with just printing string and 
 * with option -n, but not if we have some variable set with export! 
 * also it is working for only one space between it, not more!
 * in case we fine $, we should check what is next to it and do we have that
 * string in key, if not, we skip it, if we do, then we skip it and print value
 * that is in hashmap with that key
 * if there is $ and space, we print that $
 * we should separatly look at the case when we have $(something), 
 * because that something is threated as command and print error if that command
 * doesn't exist! */

/* we are considering that before we come to this function, spaces after name 
are already skipped! */

void	ft_echo(char *input)
{
	int	i;
	int	flag;

	i = 0;
	gflag = 0;
	if (ft_strncmp(input, "-n", 2) == 1)
	{
		i += 2;
		flag = 1;
	}
	if (check_word(input, i, ft_strlen(input)) == 0)
		// error
		return ;
	
}
