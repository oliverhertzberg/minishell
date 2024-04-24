#include "../../headers/minishell.h"
//We need to create hashmap with all the env variables and with this function we print it

void	ft_env(char **env)
{
	char	*hash_key;
	char	*hash_value;
	char	**my_env;
	char	*equal_pos; //position of =
	t_hmap	*hashmap[HASHMAP_SIZE];
	int 	i;

	*hashmap[HASHMAP_SIZE] = {NULL};
	i = 0;
	my_env = env;
	while (*my_env)
	{
		*equal_pos = ft_strchr(*my_env, "=");
		if (!equal_pos)
		{
			*equal_pos = '\0';
			equal_pos++;
			add_new_var(hashmap, my_env[equal_pos], getenv(equal_pos));
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
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
		i++;
	}
	return ;
}