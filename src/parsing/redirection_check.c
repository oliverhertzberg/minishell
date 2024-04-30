#include "../../headers/minishell.h"

void    handle_redirection(char *string)
{
    int i;
    char quote_open;

    i = 0;
    quote_open = '\0';
    while (string[i])
    {
        if (!quote_open && (string[i] == '"' || string[i] == '\''))
            quote_open = string[i];
        else if (quote_open && (string[i] == '"' || string[i] == '\''))
            quote_open = '\0';
        else if (!quote_open && (string[i] == '<' || string[i] == '>'))
        {
            if (string[i] == '<' && string[i + 1] == '<')
                here_doc();
            else if (string[i] == '>' && string[i + 1] == '>')
                append_redir();
            else if (string[i] == '<')
                input_redir();
            else if (string[i] == '>')
                input_redir();
        }
        i++;    
    }
}

void    redirection_check(t_parser **p)
{
    t_parser *current;

    current = *p;
    while (current)
    {
        while (*(current->string))
        {
            if (ft_strchr("<>", *(current->string)))
            {
                handle_redirection(&current);
                break;
            }
            (current->string)++;
        }
        current = current->next;
    }
}