#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*str;
	char	*temp;

	if (!s1 || !s2 || !s3)
		return (0);
	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (0);
	str = ft_strjoin(temp, s3);
	free(temp);
	if (!str)
		return (0);
	return (str);
}

void	ft_strjoin_new(char **s1, char **s2)
{
	char	*str;
	int		i;
	int		j;

	if (!(*s1) || !(*s2))
		return (0);
	str = malloc(ft_strlen(*s1) + ft_strlen(*s2) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*s1[i] != '\0')
	{
		str[i] = *s1[i];
		i++;
	}
	j = 0;
	while (*s2[j] != '\0')
	{
		str[i] = *s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(*s1);
	free(*s2);
	*s1 = str;
}