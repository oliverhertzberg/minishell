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

void	ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	while (i < n && src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
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

int	ft_atoi_short(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != 0)
		return (-1);
	return (res);
}

/* making new string that will skill first and last character in our old
string and change it in memory */
void ft_skip_fl(char **str) //test this!!
{
	char	*new_str;
	char	*original_str;
	int		i;
	int		j;

    new_str = (char *)malloc(ft_strlen(*str) - 1);
    if (!new_str)
        malloc_error();
	// free everything!
    original_str = *str;
    i = 0;
	j = 1;
    while (original_str[j + 1] != '\0' && i < ft_strlen(*str)) {
        new_str[i] = original_str[j];
        j++;
        i++;
    }
    new_str[i] = '\0';
    free(*str); // Free memory for the old string
    *str = new_str; // Update pointer to point to the new string
}