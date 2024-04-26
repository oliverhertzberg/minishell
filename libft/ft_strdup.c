#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dest;
	int		i;

	dest = malloc(ft_strlen(str) + 1);
	i = 0;
	if (dest == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
