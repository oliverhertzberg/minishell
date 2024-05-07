#include "headers/minishell.h"

char    *get_next_word(char *string, int *i)
{
    char quote;
    int start;
    int end;

    quote = '\0';
    while (string[*i] && ft_isspace(string[*i]) == 1)
        (*i)++;
    start = *i;
    while (string[*i])
    {
        if (!quote && ft_isspace(string[*i]) == 1)
            break ;
        if (!quote && (string[*i] == '\'' || string[*i] == '"'))
            quote = string[*i];
        else if (quote && string[*i] == quote)
            quote = '\0';
        (*i)++;
    }
    end = *i;
    return (ft_parse_substr(string, start, end - start));
}

int	main(int argc, char **argv)
{
	char *string;
	int i = 0;

	printf("%s\n", argv[1]);
	
	while (argv[1][i])
	{
		string = get_next_word(argv[1], &i);
		printf("%s\n", string);
        free (string);
	}

	return (0);
}
