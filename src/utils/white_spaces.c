#include "../../headers/utils.h"

static int	count_char(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	while (str[i] != 0)
	{
		i++;
		n++;
	}
	if (i > 0)
	{
		i--;
		while (i != 0 && ft_isspace(str[i]) == 1)
		{
			i--;
			n--;
		}
	}
	return (n);
}

/* stripping white spaces from beginning and from the end */
void	ft_strip(char **str)
{
	int		count;
	char	*new_str;
	char	*original_str;
	int		i;

	if (!str || !*str)
		return ;
	count = count_char(*str);
	new_str = (char *)malloc(count + 1);
	if (!new_str)
		malloc_error();
	// free everything!
	original_str = *str;
	i = 0;
	while (ft_isspace(*original_str) == 1)
		original_str++;
	while (*original_str != '\0' && i < count)
	{
		new_str[i] = *original_str;
		original_str++;
		i++;
	}
	new_str[i] = '\0';
	free(*str);
	*str = new_str;
}
