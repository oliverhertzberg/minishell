#include "../../headers/minishell.h"

/* initializing hashmap and check what is happaning when env is empty */
t_hmap	**init_hmap(char **env)
{
	char	*hash_key;
	char	*equal_pos; //position of =
	t_hmap	**hashmap;
	int		len;

	hashmap = NULL;
	while (*env)
	{
		equal_pos = ft_strchr(*env, '=');
		if (!equal_pos)
		{
			len = equal_pos - *env;
			hash_key = (char *)malloc(len + 1);
			ft_strncpy(hash_key, *env, len);
			hash_key[len] = '\0';
			add_new_var(hashmap, hash_key, getenv(hash_key));
		}
		env++;
	}
	return (hashmap);
}

/* is_env == 1 if we are printing env, which means that u should also print "_",
is_env == 0 if we are printing export, which means that u should not print "_" */
void	ft_env(t_hmap *hashmap, int is_env)
{
	int		i;

	i = 0;
	while (hashmap)
	{
		if (hashmap->value && hashmap->value != '\0')
		{
			if (is_env == 1)
				printf("%s=%s\n", hashmap->key, hashmap->value);
			else if (is_env == 0)
			{
				if (ft_strcmp(hashmap->key, "_") != 0)
					printf("declare -x %s=\"%s\"\n", hashmap->key, hashmap->value);
				else
					printf("_=\"/bin/bash\"\n");
			}
		}
		hashmap = hashmap->next;
		i++;
	}
	return ;
}
