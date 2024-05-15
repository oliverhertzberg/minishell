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
void	ft_export(char *input, int *i, t_hmap **hsmap)
{
	char	*key;
	char	*value;

	if (!input)
		ft_env(*hsmap, 0);
	while (ft_isspace(input[*i]) == 1)
    	(*i)++;
	if (input[*i] == 0)
	    ft_env(*hsmap, 0);
	while (input[*i] != 0)
	{
		while (ft_isspace(input[*i]) == 1)
	    	(*i)++;
		key = take_key(input, i);
      	value = take_value(input, i);
		if (key[ft_strlen(key) - 1] == ' ')
			export_error(key, value);
      	if (!key && value)
        	not_key_value(value);
      	else if (key && !value)
			key_not_value(key, hsmap);
      	else if (key && value)
		{//might need == instead of =
			// if ((*hsmap[0] = '\'' && *hsmap[(int)ft_strlen(**hsmap)] =  '\'') 
			// 	|| (*hsmap[0] = '"' && *hsmap[(int)ft_strlen(**hsmap)] =  '"'))
			// {
			key = take_key(input, (int *)1);
			value = take_value(input, (int *)ft_strlen(key) + 1);
			// }
			key_value(key, value, hsmap);
		}
    	(*i)++;
    }
}
