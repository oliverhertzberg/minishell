#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	char	*cur;
	int		len;

	s = (char *)str;
	len = ft_strlen(s);
	cur = s + len;
	while (*cur != (unsigned char)c)
	{
		if (cur == s)
			return (NULL);
		cur--;
	}
	return (cur);
}
