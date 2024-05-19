#include "../../headers/minishell.h"

/* using those functions from var_utils to actually make export work 
 * properly. take key and value from input and put it inside of some strings,
 * then check if key exists, if it does, if u have value, free old one and 
 * save new one using change_value, if u have only key, don't do anything.
 * if key doesn't exist, add it inside of v.
 * */
static void	key_value(char *key, char *value, t_hmap **hsmap)
{
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		printf("Minishell: export: \'%s=%s\': not a valid identifier\n", key, value);
		ft_free_key_value(key, value);
		return ;
	}
	check_append(hsmap, key, value);
	if (key_exists(*hsmap, key) == 1 && key[ft_strlen(key)] != '+')
    	change_value(hsmap, key, value); // check this
	else if (key_exists(*hsmap, key) == 0)
    	add_new_var(hsmap, key, value);
    // ft_free_key_value(key, value);
}
static void	key_not_value(char *key, t_hmap **hsmap) // =
{
	printf("Bla\n");
	add_new_var(hsmap, key, "");
	printf("Bla22222222\n");
    free(key);
}

static void	not_key_value(char *value)
{
	// error & free value
	printf("Minishell: export: \'=%s\': not a valid identifier\n", value);
	free(value);
}

static void	key_not_value1(char *key, t_hmap **hsmap) //no =
{
	printf("Bla\n");
	add_new_var1(hsmap, key);
	printf("Bla22222222\n");
    free(key);
}

static void export_error(char *key, char *value)
{
	if (!ft_strcmp(&value[0], " "))
		printf("Minishell: export: \'=\': not a valid identifier\n");
	else
		printf("Minishell: export: \'=%s\': not a valid identifier\n", value);
	ft_free_key_value(key, value);
}

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
		printf("!!!!!!! %s\n!!!!!!! %s\n", key, value);
		if (key[ft_strlen(key) - 1] == ' ')
			export_error(key, value);
      	if (!key && value)
        	not_key_value(value);
		else if (key && !value && ft_strchr(c->args[i], '='))
			key_not_value(key, hsmap);
		else if (key && !value && ft_strchr(c->args[i], '=') == NULL)
			key_not_value1(key, hsmap);
      	else if (key && value)
		{
			// if ((*hsmap[0] = '\'' && *hsmap[(int)ft_strlen(**hsmap)] =  '\'') 
			// 	|| (*hsmap[0] = '"' && *hsmap[(int)ft_strlen(**hsmap)] =  '"'))
			// {
			key = take_key(c->args[i]);
			value = take_value(c->args[i]);
			// }
			key_value(key, value, hsmap);
		}
    	i++;
    }
}
