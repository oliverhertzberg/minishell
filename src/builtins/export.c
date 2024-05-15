#include "../../headers/minishell.h"

/* using those functions from var_utils to actually make export work 
 * properly. take key and value from input and put it inside of some strings,
 * then check if key exists, if it does, if u have value, free old one and 
 * save new one using change_value, if u have only key, don't do anything.
 * if key doesn't exist, add it inside of v.
 * */
static void	key_value(char *key, char *value, t_hmap **hsmap)
{
	if (key[0] == '$' || (key[0] >= '0' && key[0] <= '9'))
	{
		printf("Minishell: export: \'%s=%s\': not a valid identifier\n", key, value);
		ft_free_key_value(key, value);
		return ;
	// }
	// if ((is_inside_quotes(key, 0, (int)ft_strlen(key)) == -1) 
	// 	|| (is_inside_quotes(value, 0, (int)ft_strlen(value)) == -1))
	// 	return ;
	// else if ((is_inside_quotes(key, 0, (int)ft_strlen(key)) == 3)
	// 	|| (is_inside_quotes(value, 0, (int)ft_strlen(value)) == 3))
	// {
	// 	//something
	}
	check_append(hsmap, key, value);
	if (key_exists(*hsmap, key) == 1 && key[ft_strlen(key)] != '+')
    	change_value(hsmap, key, value); // check this
	else if (key_exists(*hsmap, key) == 0)
    	add_new_var(hsmap, key, value);
    ft_free_key_value(key, value);
}
static void	key_not_value(char *key, t_hmap **hsmap)
{
	add_new_var(hsmap, key, "");
    free(key);
}

static void	not_key_value(char *value)
{
	// error & free value
	printf("Minishell: export: \'=%s\': not a valid identifier\n", value);
	free(value);
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
void	ft_export(char *input, t_hmap *hsmap)
{
	char	*key;
	char	*value;
	int 	i;

	i = 0;
	printf("BLAAAA11111\n");
	if (input[i] == '\0')
	{
		printf("BLAAAAwwvww\n");
	    ft_env(hsmap, 0);
	}
	printf("BLAAAA\n");
	while (ft_isspace(input[i]) == 1)
    	i++;
	while (input[i] != 0)
	{
		printf("BLA\n");
		while (ft_isspace(input[i]) == 1)
	    	i++;
		printf("BLAAAA\n");
		key = take_key(input, &i);
		printf("BLA 2\n");
      	value = take_value(input, &i);
		printf("BLA 3\n");
		if (key[ft_strlen(key) - 1] == ' ')
			export_error(key, value);
      	if (!key && value)
        	not_key_value(value);
      	else if (key && !value)
			key_not_value(key, &hsmap);
      	else if (key && value)
		{
			// if ((*hsmap[0] = '\'' && *hsmap[(int)ft_strlen(**hsmap)] =  '\'') 
			// 	|| (*hsmap[0] = '"' && *hsmap[(int)ft_strlen(**hsmap)] =  '"'))
			// {
			printf("BLA 4\n");
			key = take_key(input, (int *)1);
			printf("BLA 5\n");
			value = take_value(input, (int *)ft_strlen(key) + 1);
			printf("BLA 6\n");
			// }
			key_value(key, value, &hsmap);
			printf("BLA 7\n");
		}
    	i++;
    }
}
