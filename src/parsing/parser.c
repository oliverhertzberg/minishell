#include "../../headers/minishell.h"

void    here_doc(t_parser **struct, char *string, int *i)
{
    git
}

void    handle_redirection(t_parser **struct, char *string, int *i)
{
    if (string[*i] == '<' && string[*i + 1] == '<')
        here_doc(struct, string, i);
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

