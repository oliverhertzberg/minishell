#include "../../headers/minishell.h"

/* using those functions from var_utils to actually make export work 
 * properly. take key and value from input and put it inside of some strings,
 * then check if key exists, if it does, if u have value, free old one and 
 * save new one using change_value, if u have only key, don't do anything.
 * if key doesn't exist, add it inside of v.
 * */
static void	key_error(char *key, char *value)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		if (value)
			printf("Minishell: export: \'%s=%s\': not a valid identifier\n", key, value);
		else
			printf("Minishell: export: \'%s\': not a valid identifier\n", key);
		ft_free_key_value(key, value);
		return ;
	}
	i = 1;
	while (key[i] != 0)
	{
		if (!ft_isalpha(key[i]) && key[i] != '_' && !ft_isdigit(key[i]))
		{
			if (value)
				printf("Minishell: export: \'%s=%s\': not a valid identifier\n", key, value);
			else
				printf("Minishell: export: \'%s\': not a valid identifier\n", key);
			ft_free_key_value(key, value);
			return ;
		}
		i++;
	}

	//check_append(hsmap, key, value);
	// if (key_exists(*hsmap, key) == 1 && key[ft_strlen(key)] != '+')
    // 	change_value(hsmap, key, value);
	// else if (key_exists(*hsmap, key) == 0)
    // 	add_new_var(hsmap, key, value);
    // ft_free_key_value(key, value);
}

static void	add_key_value(char *key, char *value, t_hmap **hsmap)
{
	if (key_exists(*hsmap, key) == 1)
    	change_value(hsmap, key, value);
	else
    	add_new_var(hsmap, key, value);
    //ft_free_key_value(key, value);
}

static void	key_not_value(char *key, t_hmap **hsmap) // =
{
	add_new_var(hsmap, key, "");
    //free(key);
}

static void	not_key_value(char *value)
{
	// error & free value
	printf("Minishell: export: \'=%s\': not a valid identifier\n", value);
	//free(value);
}

static void	key_not_value1(char *key, t_hmap **hsmap) //no =
{
	add_new_var1(hsmap, key);
    //free(key);
}

// static void export_error(char *key, char *value)
// {
// 	if (!ft_strcmp(&value[0], " "))
// 		printf("Minishell: export: \'=\': not a valid identifier\n");
// 	else
// 		printf("Minishell: export: \'=%s\': not a valid identifier\n", value);
// 	ft_free_key_value(key, value);
// }

//check what the exit_status should be
void	ft_export(t_cmd_data *c, t_hmap **hsmap)
{
	char	*key;
	char	*value;
	int 	i;

	i = 1;
	if (c->args[i] == NULL)
	   ft_env(*hsmap, 0);
	while (c->args[i] != NULL)
	{
		key = take_key(c->args[i]);
      	value = take_value(c->args[i]);
		printf("------------------\n");
		printf("%s %s %s\n", key, value, c->args[i]);
		key_error(key, value);
		printf("%s %s %s\n", key, value, c->args[i]);
      	if (!key && value)
		{
        	not_key_value(value);
			printf("1 %s\n", c->args[i]);
		}
		else if (key && !value && ft_strchr(c->args[i], '=') != NULL)
		{
			key_not_value(key, hsmap);
			printf("2 %s\n", c->args[i]);
		}
		else if (key && !value && ft_strchr(c->args[i], '=') == NULL)
		{
			key_not_value1(key, hsmap);
			printf("3 %s\n", c->args[i]);
		}
      	else if (key && value && ft_strcmp(value, "") != 0)
		{
			// key = take_key(c->args[i]);
			// value = take_value(c->args[i]);
			printf("%s %s\n", key, value);
			add_key_value(key, value, hsmap);
			printf("%s %s\n", key, value);
			printf("4 %s\n", c->args[i]);
		}
		ft_free_key_value(key, value);
    	i++;
    }
}
