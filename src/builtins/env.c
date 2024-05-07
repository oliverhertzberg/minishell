#include "../../headers/minishell.h"

/* initializing hashmap and check what is happaning when env is empty */
t_hmap	**init_hmap(char **env)
{
	char	*hash_key;
	t_hmap	**hashmap;
	int		j;
	int		i;

	hashmap = (t_hmap **)malloc(sizeof(t_hmap *));
	if (!hashmap)
		exit(EXIT_FAILURE); //fail to malloc
	*hashmap = NULL;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != 0 && env[i][j] != '=')
			j++;
		hash_key = malloc(j + 1);
		if (!hash_key)
		{
			printf("malloc fail!");
			exit(EXIT_FAILURE);
		}
		ft_strncpy(hash_key, env[i], j);
		add_new_var(hashmap, hash_key, ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (hashmap);
}

/* is_env == 1 if we are printing env, which means that u should also print "_",
is_env == 0 if we are printing export, which means that u should not print "_" */
void	ft_env(t_hmap *hashmap, int is_env)
{
	while (hashmap)
	{
		if (is_env == 1)
			printf("%s=%s\n", hashmap->key, hashmap->value);
		else
		{
			if (ft_strcmp(hashmap->key, "_") != 0)
				printf("declare -x %s=\"%s\"\n", hashmap->key, hashmap->value);
			else
				printf("declare -x _=\"/bin/bash\"\n");
		}
		hashmap = hashmap->next;
	}
}
