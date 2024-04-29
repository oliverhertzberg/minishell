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
void	ft_echo(char *input)
{
	if (is_substr(input, "-n") == 1)
		printf("%s", input + 8);
	else
		printf("%s\n", input + 5);
}
