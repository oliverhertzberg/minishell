#include "../../headers/minishell.h"
//We need to create hashmap with all the env variables and with this function we print it

void	insert_env(t_hmap	**hashmap, char *key, char *value)
{

}

void	ft_env(char **env)
{
	char	*hash_key;
	char	*hash_value;
	free_t_hmap	

	print_map(hashmap);
}

void	print_map(t_hmap **hashmap)
{
	while (hashmap)
	{
		if (hashmap->value && hashmap->value != '\0')
			printf("%s=%s\n", hashmap->name, hashmap->value);
		hashmap = hashmap->next;
	}
	return ;
}