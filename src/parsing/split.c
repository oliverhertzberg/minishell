#include "../../headers/minishell.h"
/*
static void in_quote(char *input, int *i, char *quote, t_parser **p)
{
    while (input[*i] != *quote && input[*i])
        (*i)++;
    if (input[*i] == *quote)
        *quote = 0;
    else
    {
        lstclear(p); // make sure everything else is freed not only list!
        quote_error();
    }
}

static t_parser *create_node(char *input, int start, int end)
{
    char *string;
    t_parser *new;

    string = (char *)malloc(sizeof(char) * (end - start));
    if (!string)
        // free everything
        malloc_error();
    ft_strncpy(string, input + start, end - start);
    if (string == NULL)
        malloc_error();
    string[end - start] = '\0';
    new = (t_parser *)malloc(sizeof(t_parser));
    if (!new)
        //error
        exit(EXIT_FAILURE);
    ft_strip(&string);
    new = lstnew(string);
    //free(string);
    return (new);
}

void    split_by_pipe(t_parser **p, char *input)
{
    int i;
    int start;
    char quote;
    t_parser *new;

    i = 0;
    quote = 0;
    while (input[i])
    {
        start = i;
        while (input[i] != '|' && input[i])
        {
            if (input[i] == '"' || input[i] == '\'')
            {
                quote = input[i++];
                in_quote(input, &i, &quote, p);
            }
            i++;
        }
        new = create_node(input, start, i);
        lstadd_back(p, new);
        // allocate memory and copy from start to i into *p->string
        if (input[i] == '|')
            i++;
    }
}*/
