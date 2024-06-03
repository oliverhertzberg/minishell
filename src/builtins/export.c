#include "../../headers/minishell.h"

static void	key_error(char *key, char *value)
{
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		if (value)
			printf("Minishell: export: \'%s=%s\': not a valid identifier\n",
				key, value);
		else
			printf("Minishell: export: \'%s\': not a valid identifier\n", key);
		ft_free_key_value(key, value);
		return ;
	}
}

static int	key_error1(char *key, char *value)
{
	int	i;

	i = 1;
	while (key[i] != 0)
	{
		if (!ft_isalpha(key[i]) && key[i] != '_' && !ft_isdigit(key[i]))
		{
			if (value)
				printf("Minishell: export: \'%s=%s\': not a valid identifier\n",
					key, value);
			else
				printf("Minishell: export: \'%s\': not a valid identifier\n",
					key);
			ft_free_key_value(key, value);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	add_key_value(char *key, char *value, t_hmap **hsmap)
{
	if (key_exists(*hsmap, key) == 1)
		change_value(hsmap, key, value);
	else
		add_new_var(hsmap, key, value);
}

//check what the exit_status should be
void	ft_export(t_cmd_data *c, t_hmap **hsmap)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	if (c->args[i] == NULL)
		ft_env(*hsmap, 0);
	while (c->args[i] != NULL)
	{
		key = take_key(c->args[i]);
		value = take_value(c->args[i]);
		if (!key && value)
		{
			printf("Minishell: export: \'=%s\': not a valid identifier\n",
				value);
			free(value);
		}
		else if (!ft_isalpha(key[0]) && key[0] != '_')
			key_error(key, value);
		else if (key_error1(key, value) == 0)
			return ;
		else
		{
			remove_var(hsmap, key);
			if (key && !value && ft_strchr(c->args[i], '=') != NULL)
				add_new_var(hsmap, key, "");
			else if (key && !value && ft_strchr(c->args[i], '=') == NULL)
				add_new_var1(hsmap, key);
			else if (key && value && ft_strcmp(value, "") != 0)
				add_key_value(key, value, hsmap);
			ft_free_key_value(key, value);
		}
		i++;
	}
}
