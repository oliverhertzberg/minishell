#include "../../headers/minishell.h"

void	ft_env(char **env)
{
	char	*hash_key;
	char	**my_env;
	char	*equal_pos; //position of =
	t_hmap	*hashmap[HASHMAP_SIZE];
	int 	i;
	int		len;

	*hashmap[HASHMAP_SIZE] = {NULL};
	my_env = env;
	while (*my_env)
	{
		*equal_pos = ft_strchr(*my_env, "=");
		if (!equal_pos)
		{
			len = equal_pos - *my_env;
			*hash_key = (char *)malloc(len + 1);
			ft_strncpy(hash_key, *my_env, len);
			hash_key[len] = '\0';
			add_new_var(hashmap, hash_key, getenv(hash_key));
			i++;
		}
		my_env++;
	}
	print_map(hashmap);
}

void	print_map(t_hmap **hashmap)
{
	t_hmap	*current;
	int		i;

	i = 0;
	*current = hashmap[i];
	while (current && i < HASHMAP_SIZE)
	{
		if (current->value && current->value != '\0')
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
		i++;
	}
	return ;
}
