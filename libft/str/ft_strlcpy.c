#include "../headers/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_length;

	src_length = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (i < src_length && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_length);
}
