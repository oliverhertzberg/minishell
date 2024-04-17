#include "../../headers/utils.h"

int	is_substr(char *str, char *sub)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != 0)
	{
		j = 0;
		if (str[i] == sub[0])
		{
			while (sub[j] != 0 && sub[j] == str[i])
			{
				i++;
				j++;
			}
			if (sub[j] == 0)
				return (1);
		}
		else
			i++;
	}
	return (0);
}
