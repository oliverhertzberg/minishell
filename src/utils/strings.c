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

char	*ft_strncpy(char *dest, char *src, int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (*(src + i) != '\0'))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	while (i < n)
	{
		*(dest + i) = '\0';
		i++;
	}
	return (dest);
}

/* 
	if character is inside of strng, it returns position of character,
	of return -1 if character is not inside
*/
int	is_in_str(char *str, char c, int start, int end)
{
	int	i;

	i = start;
	while (i < end && str[i] != 0)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
