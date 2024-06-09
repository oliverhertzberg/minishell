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

static int	export_help_err(char *key, char *value)
{
	if (!key && !value)
	{
		printf("Minishell: export: : not a valid identifier\n");
		return (1);
	}
	else if (!key && value)
	{
		printf("Minishell: export: \'=%s\': not a valid identifier\n",
			value);
			return (1);
	}
	return (0);
}

static void	export_help(char *input, t_hmap **hsmap, int *errorcode)
{
	char	*key;
	char	*value;

	key = take_key(input);
	value = take_value(input);
	if (export_help_err(key, value) == 1)
	{
		*errorcode = 1;
		exit(EXIT_FAILURE);
	}
	if (!ft_isalpha(key[0]) && key[0] != '_')
		key_error(key, value);
	else if (key_error1(key, value) == 0)
		return ;
	else
	{
		remove_var(hsmap, key);
		if (key && !value && ft_strchr(input, '=') != NULL)
			add_new_var(hsmap, key, "");
		else if (key && !value && ft_strchr(input, '=') == NULL)
			add_new_var1(hsmap, key);
		else if (key && value && ft_strcmp(value, "") != 0)
			add_key_value(key, value, hsmap);
	}
}

void	ft_export(t_cmd_data *c, t_hmap **hsmap)
{
	int		i;

	i = 1;
	if (c->args[i] == NULL)
		ft_env(*hsmap, 0);
	while (c->args[i] != NULL)
	{
		export_help(c->args[i], hsmap, &c->env_ptr->exit_code);
		i++;
	}
}
