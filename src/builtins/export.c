#include "../../headers/builtins.h"

/* using those functions from var_utils to actually make export work 
 * properly. take key and value from input and put it inside of some strings,
 * then check if key exists, if it does, if u have value, free old one and 
 * save new one using change_value, if u have only key, don't do anything.
 * if key doesn't exist, add it inside of v.
 * */
static void	key_value(char *key, char *value, t_builtins *b, t_hmap **hsmap)
{
	if (key_exists(b->hsmap, key) == 1)
    	change_value(b->hsmap, key, value); // check this
	else
    	add_new_var(b->hsmap, key, value);
    free(key);
    free(value);
}
static void	key_not_value(char *key, char *value, t_builtins *b, t_hmap **hsmap)
{
	add_new_var(b->hsmap, key, "");
    	free(key);
}

static void	not_key_value(char *key, char *value, t_builtins *b, t_hmap **hsmap)
{
	// error & free value

}

static void export_error(char *key, char *value, t_builtins *b, t_hmap **hsmap)
{
	if (value[0] == " ")
		printf("Minishell: export: \'=\': not a valid identifier\n");
	else
		printf("Minishell: export: \'=%s\': not a valid identifier\n", value);
	free(key);
	free(value);
}


//check what the exit_status should be
void	ft_export(char *input, t_builtins *b, int *i, t_hmap **hsmap)
{
	char	*key;
	char	*value;

	while (ft_isspace(input[*i]) == 1)
    	*i++;
	if (input[*i] == 0)
	    ft_env(hsmap, 0);
	while (input[*i] != 0)
	{
		while (ft_isspace(input[*i]) == 1)
	    	*i++;
		key = take_key(input, i);
      	value = take_value(input, i);
		if (key[ft_strlen(key) - 1] == ' ')
			export_error(key, value, b, hsmap);
      	if (!key && value)
        	not_key_value(key, value, b, hsmap);
      	else if (key && !value)
			key_not_value(key, value, b, hsmap);
      	else if (key && value)
			key_value(key, value, b, hsmap);
    	*i++;
    }
}
