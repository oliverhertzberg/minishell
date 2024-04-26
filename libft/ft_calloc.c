#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*el;
	size_t	num;

	num = 0;
	if (nitems != 0 && (4611686014132420608 / nitems) < size)
		return (0);
	num = nitems * size;
	el = malloc(num);
	if (!el)
		return (0);
	ft_bzero(el, num);
	return (el);
}
