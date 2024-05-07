#include "../../headers/minishell.h"

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

static void    create_node(t_parser *new, char *input, int start, int end)
{
    char *string;

    string = (char *)malloc(sizeof(char) * (end - start + 1));
    if (!string)
        // free everything
        malloc_error();
    ft_strlcpy(string, input + start, end - start + 1);
    if (string == NULL)
        malloc_error();
    *string = '\0';
    new = lstnew(string);
    //free(string);
}

void    split_by_pipe(t_parser **p, char *input)
{
    int i;
    int start;
    char quote;
    t_parser *new;

    i = 0;
    quote = 0;
    p = NULL;
    new = (t_parser *)malloc(sizeof(t_parser));
    if (!new)
        //error
        return ;
    printf("bla 1\n");
    while (input[i])
    {
        printf("bla 2\n");
        start = i;
        while (input[i] != '|' && input[i])
        {
            printf("bla 3\n");
            if (input[i] == '"' || input[i] == '\'')
            {
                quote = input[i++];
                in_quote(input, &i, &quote, p);
            }
            i++;
        }
        printf("bla 4\n");
        create_node(new, input, start, i);
        lstadd_back(p, new);
        printf("%s\n", (*p)->string);
        // allocate memory and copy from start to i into *p->string
        if (input[i] == '|')
            i++;
    }
    printf("bla 4\n");
}
