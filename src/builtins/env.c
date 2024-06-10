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
		exit(EXIT_FAILURE);
	*hashmap = NULL;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != 0 && env[i][j] != '=')
			j++;
		hash_key = malloc(j + 1);
		if (!hash_key)
			exit(1);
		ft_strncpy(hash_key, env[i], j);
		add_new_var(hashmap, hash_key, ft_strchr(env[i], '=') + 1);
		free(hash_key);
		i++;
	}
	return (hashmap);
}

/* 
is_env == 1 if we are printing env, which means that u should also print "_",
is_env == 0 if we are printing export, which means that u should not print "_" 
*/
// t_cmd_data **c
// t_cmd_data->env_ptr->exit_code
void	ft_env(t_hmap *hsmap, int is_env)
{
	while (hsmap)
	{
		if (is_env == 1)
		{
			if (hsmap->value != NULL && hsmap->show == 1)
				printf("%s=%s\n", hsmap->key, hsmap->value);
		}
		else
		{
			if (hsmap->value == NULL)
			{
				if (ft_strcmp(hsmap->key, "_") != 0)
					printf("declare -x %s\n", hsmap->key);
			}
			else
			{
				if (ft_strcmp(hsmap->key, "_") == 0)
					printf("declare -x _=\"/bin/bash\"\n");
				else if (hsmap->show == 1)	
					printf("declare -x %s=\"%s\"\n", hsmap->key,
						hsmap->value);
					
			}
		}
		hsmap = hsmap->next;
	}
}

/* size of hashmap */
int	hashmap_size(t_hmap *hashmap)
{
	int	size;

	size = 0;
	while (hashmap)
	{
		size++;
		hashmap = hashmap->next;
	}
	return (size);
}

/* putting env in array of strings */
char	**env_to_str(t_hmap *h)
{
	char	**str;
	int		i;

	str = (char **)malloc(sizeof(char *) * (hashmap_size(h) + 1));
	if (!str)
		exit(1);
	i = 0;
	while (h)
	{
		if (h->value == NULL)
			str[i] = ft_strdup(h->key);
		else
		{
			str[i] = malloc(ft_strlen(h->key) + ft_strlen(h->value) + 1);
			if (!str[i])
				exit(1);
			str[i] = ft_strjoin3(h->key, "=", h->value);
			if (!str[i])
				exit(1);
			h = h->next;
		}
		i++;
	}
	str[i] = 0;
	return (str);
}
