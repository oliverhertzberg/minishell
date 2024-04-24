#include "../../headers/minishell.h"

void in_quote(char *input, int *i, char *quote, t_parser **p)
{
    while (input[*i] != *quote && input[*i])
        (*i)++;
    if (input[*i] == *quote)
        *quote = 0;
    else
    {
        // error
        lstclear(p);
        exit(1);
    }
}

void    create_node(t_parser *new, char *input, int start, int end)
{
    char *string;

    string = (char *)malloc(sizeof(char) * (end - start + 1));
    if (string == NULL)
        // error
        return (1);
    new = lstnew(string);
    free (string);
}

void    split_parser(t_parser **p, char *input)
{
    int i;
    int start;
    char quote;
    t_parser *new;

    i = 0;
    quote = 0;
    p = NULL;
    while(input[i])
    {
        start = i;
        while (input[i] != '|' && input[i])
        {
            if (input[i] == '"' || input[i] == "'")
            {
                quote = input[i++];
                in_quote(input, &i, quote, p);
            }
            i++;
        }
        create_node(new, input, start, i);
        lstadd_back(p, new);
        // allocate memory and copy from start to i into *p->string
        if (input[i] == '|')
            i++;
    }
}
