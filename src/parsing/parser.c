#include "../../headers/minishell.h"

char    *get_next_word(char *string, int *i)
{
    char quote;
    int start;
    int end;

    quote = '\0';
    while (string[*i] && ft_isspace(string[*i]) == 1)
        (*i)++;
    start = *i;
    if (string[*i] == '\'' || string[*i] == '"')
        start = *i + 1;
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
    if (string[*i - 1] == '\'' || string[*i - 1] == '"')
        end = *i - 1;
    else
        end = *i;
    return (ft_substr(string, start, end - start));
}

void    retrieve_heredoc(char *delimiter, int heredoc_fd)
{
    char    *buf;

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
        write (heredoc_fd, buf, ft_strlen(buf));
        free (buf);
    }
    if (buf)
        free (buf);
}
void    get_file_name(char **filename)
{
    static int file_num = 0;
    char    *new_name;
    char    *string_num;

    string_num = ft_itoa(file_num);
    // malloc error
    new_name = ft_strjoin(*filename, string_num);
    // malloc error
    free (*filename);
    free (string_num);
    *filename = new_name;
    file_num++;
}

void    here_doc(t_parser **table, char *string, int *i)
{
    char    *delimiter;
    char    *file_name;
    int     fd;

    *i += 2;
    file_name = (char *)malloc(10);
    ft_strlcpy(file_name, "here_doc.", 10);
    get_file_name(&file_name);
    if ((delimiter = get_next_word(string, i)) == NULL)
        // malloc error
    if ((fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
        // open error
    file_lstadd_back(&((*table)->heredoc),file_lstnew(file_name, fd, 0));
    retrieve_heredoc(delimiter, (*table)->heredoc->fd);
    (*table)->heredoc = 1;
}

void    input_redirection(t_parser **table, char *string, int *i)
{
    char *infile;

    *i += 1;
    if ((infile = get_next_word(string, i)) == NULL)
            exit (1);
            // malloc error
    file_lstadd_back(&((*table)->infile), file_lstnew(infile, -2, 0));
}

void    output_redirection(t_parser **table, char *string, int *i, int append)
{
    char *outfile;

    if (append == 0)
        (*i)++;
    else if (append == 1)
        (*i) += 2;
    if ((outfile = get_next_word(string, i)) == NULL)
            exit (1);
            // malloc error
    file_lstadd_back(&((*table)->outfile), file_lstnew(outfile, -2, 1));
}

void    handle_redirection(t_parser **table, char *string, int *i)
{
    if (string[*i] == '<' && string[*i + 1] == '<')
        here_doc(table, string, i);
    else if (string[*i] == '<')
        input_redirection(table, string, i);
    else if (string[*i] == '>' && string[*i + 1] == '>')
        output_redirection(table, string, i, 1);
    else if (string[*i] = '>')
        output_redirection(table, string, i, 0);
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
}

