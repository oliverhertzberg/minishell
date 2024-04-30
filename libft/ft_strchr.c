#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*s;

	s = (char *)str;
	while (*s != (unsigned char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return (s);
}
