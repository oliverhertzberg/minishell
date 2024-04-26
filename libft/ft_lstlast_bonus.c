#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*node;

	if (!lst)
		return (NULL);
	node = lst;
	while (node -> next != NULL)
	{
		node = node -> next;
	}
	return (node);
}
