#include "../../headers/minishell.h"
/*
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

void    here_doc(t_parser **table, char *string, int *i)
{
    char *delimiter;
    char *buf;

    if ((delimiter = get_next_word(string, i)) == NULL)
        // malloc error
    if (((*table)->fd_here_doc = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
        // open error
    while (1)
    {
        write(1, ">", 2);
        buf = get_next_line(0);
        if (!buf)
            break ;
        if (buf < 0)
            // error
        if (ft_strncmp(buf, delimiter, ft_strlen(delimiter) == 0)
            && buf[ft_strlen(delimiter)] == '\n')
            break;
        write ((*table)->fd_here_doc, buf, ft_strlen(buf));
        free (buf);
    }
    if (buf)
        free (buf);
    close ((*table)->fd_here_doc);
}

void    handle_redirection(t_parser **table, char *string, int *i)
{
    if (string[*i] == '<' && string[*i + 1] == '<')
    {
        *i += 2;
        here_doc(table, string, i);
    }
    else if (string[*i] == '<')
    {
        *i += 1;
        if (((*table)->infile = get_next_word(string, i)) == NULL)
            exit (1);
            // malloc error
    }
    else if (string[*i] == '>' && string[*i + 1] == '>')
        append_output();
    else if (string[*i] = '>')
        output_redirection();
}

void    handle_command(t_parser **table, char *quote, int *i)
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
            while(ft_isspace((current->string)[i]) == 1)
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
}*/

