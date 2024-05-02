#include "../../headers/minishell.h"

char    *get_next_word(char *string, int *i)
{
    char quote;
    int start;
    int end;

    quote = '\0';
    while (string[*i] && string[*i] == ' ')
        (*i)++;
    start = *i;
    if (string[*i] == '\'' || string[*i] == '"')
        start = *i + 1;
    while (string[*i])
    {
        if (!quote && string[*i] == ' ')
            break ;
        if (!quote && (string[*i] == '\'' || string[*i] == '"'))
            quote = string[*i];
        else if (quote && string[*i] == quote)
            quote = '\0';
        (*i)++;
    }
    if (string[*i - 1] == '\'' || string[*i - 1] == '"')
        end = *i - 1;
    else
        end = *i;
    return (ft_substr(string, start, end - start));
}

void    here_doc(t_parser **struct, char *string, int *i)
{
    char *delimiter;
    char *buf;

    delimiter = get_next_word(string, i);
    if (access(".here_doc", F_OK))
        unlink(".here_doc");
    *struct->
}

void    handle_redirection(t_parser **struct, char *string, int *i)
{
    if (string[*i] == '<' && string[*i + 1] == '<')
    {
        *i += 2;
        here_doc(struct, string, i);
    }
    else if (string[*i] == '<')
        input_redirection();
    else if (string[*i] == '>' && string[*i + 1] == '>')
        append_output();
    else if (string[*i] = '>')
        output_redirection();
}

void    handle_command(t_parser **struct, char *quote, int *i)
{

}

void    parse_string(t_parser **p)
{
    t_parser *current;
    int i;
    char    quote;

    current = *p;
    i = 0;
    quote = '\0';
    while (current)
    {
        while ((current->string)[i])
        {
            while((current->string)[i] == ' ')
                i++;
            if (!quote && ((current->string)[i] == '\'' || (current->string)[i] == '"'))
                quote = (current->string)[i];
            else if (!quote && ((current->string)[i] == '<' || (current->string)[i] == '>'))
                handle_redirection(&current, current->string, &i);
            else
                handle_command(&current, &quote, &i);
            i++;
        }
        current = current->next;
    }
}

