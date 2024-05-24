#include "../../headers/minishell.h"

static void single_quote(char *str, char *new_str, int *j)
{
    char    *temp;
    int     start;

    (*j)++;
    start = *j;
    if (str[*j] == '\'')
    {
        (*j)++;
        return ;
    }
    while (str[*j] != '\'' && str[*j] != 0)
        (*j)++;
    if (str[*j] == 0 && str[*j - 1] != '\'') // open quotes
            //error
            exit(EXIT_FAILURE);
    temp = ft_substr(str, (unsigned int)start, *j - start + 1);
    if (!temp)
        //error
        exit(EXIT_FAILURE);
    ft_strjoin_new(&new_str, &temp);
}

static void handle_dolar_double(char *str, char *new_str, int *j)
{
    char    *temp;
    int     start;

    (*j)++;
    start = *j;
    if (str[*j] == 0 || (ft_isalpha(str[*j]) == 0 && str[*j] != '_'))
    {
        ft_strjoin_new(&new_str, "$");
        return ;
    }
    while (str[*j] != 0 && (ft_isalpha(str[*j]) || ft_isdigit(str[*j]) || str[*j] == '_'))
        (*j)++;
    temp = ft_substr(str, (unsigned int)start, *j - start + 1);
    if (!temp)
        //error
        exit(EXIT_FAILURE);
    ft_strjoin_new(&new_str, &temp);
}

static void double_quote(char *str, char *new_str, int *j) //check this
{
    int     start;
    char    *temp;

    (*j)++;
    start = *j;
    if (str[*j] == '"')
    {
        (*j)++;
        return ;
    }
    while (str[*j] != '"' && str[*j] != 0)
    {
        if (str[*j] == '$')
        {
            temp = ft_substr(str, (unsigned int)start, *j - start + 1);
            if (!temp)
                //error
                 exit(EXIT_FAILURE);
            ft_strjoin_new(&new_str, &temp);
            start = *j;
            handle_dolar_double(str, new_str, j);
            start = *j;
        }
        (*j)++;
    }
    ft_strjoin_new(&new_str, &temp);
}

static void handle_dolar_alone(char *str, char *new_str, int *j)
{
    char    *temp;
    int     start;

    (*j)++;
    start = *j;
    if (str[*j] == 0 || (ft_isalpha(str[*j]) == 0 && str[*j] != '_' && str[*j] != '\'' && str[*j] != '"'))
    {
        ft_strjoin_new(&new_str, "$");
        return ;
    }
    if (str[*j] == '\'')
        single_quote(str, new_str, j);
    if (str[*j] == '"')
        double_quote(str, new_str, j);
    while (str[*j] != 0 && (ft_isalpha(str[*j]) || ft_isdigit(str[*j]) || str[*j] == '_'))
        (*j)++;
    temp = ft_substr(str, (unsigned int)start, *j - start + 1);
    if (!temp)
        //error
        exit(EXIT_FAILURE);
    ft_strjoin_new(&new_str, &temp);
}

static void no_quotes(char *str, char *new_str, int *j)
{
    char    *temp;
    int     start;

    start = *j;
    while (str[*j] != '"' && str[*j] != '\'' && str[*j] != 0)
    {
        while (str[*j] != '$' && str[*j] != '"' && str[*j] != '\'' && str[*j] != 0)
            (*j)++;
        temp = ft_substr(str, (unsigned int)start, *j - start + 1);
        if (!temp)
            //error
            exit(EXIT_FAILURE);
        ft_strjoin_new(&new_str, &temp);
        if (str[*j] == '$')
            handle_dolar_alone(str, new_str, j);
    }
    if (str[*j] == '"' && str[*j] == '\'')
        (*j)--;
}

void    clean_dolar(t_cmd_data **d)
{
    int     i;
    int     j;
    char    *new_str;

    i = 0;
    j = 0;
    new_str = NULL;
    while ((*d)->args[i])
    {
        if (check_word((*d)->args[i], 0, ft_strlen((*d)->args[i]) == 0))
            //error open quotes
            exit(EXIT_FAILURE);
        while ((*d)->args[i][j])
        {
            if ((*d)->args[i][j] == '\'')
                single_quote((*d)->args[i], new_str, &j);
            if ((*d)->args[i][j] == '"')
                double_quote((*d)->args[i], new_str, &j);
            else
                no_quotes((*d)->args[i], new_str, &j);
            j++;
        }
        free((*d)->args[i]);
        (*d)->args[i] = ft_strdup(new_str);
        free(new_str);
        i++;
    }
}