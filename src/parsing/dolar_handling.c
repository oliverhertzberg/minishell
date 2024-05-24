#include "../../headers/minishell.h"

static void single_quote(char *str, char **new_str, int *j)
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
    ft_strjoin_new(new_str, &temp);
}

static void handle_dolar_double(char *str, char **new_str, int *j)
{
    char    *temp;
    int     start;

    (*j)++;
    start = *j;
    if (str[*j] == 0 || (ft_isalpha(str[*j]) == 0 && str[*j] != '_'))
    {
        temp = ft_strdup("$");
        ft_strjoin_new(new_str, &temp);
        return ;
    }
    while (str[*j] != 0 && (ft_isalpha(str[*j]) || ft_isdigit(str[*j]) || str[*j] == '_'))
        (*j)++;
    temp = ft_substr(str, (unsigned int)start, *j - start + 1);
    if (!temp)
        //error
        exit(EXIT_FAILURE);
    ft_strjoin_new(new_str, &temp);
}

static void double_quote(char *str, char **new_str, int *j) //check this
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
            ft_strjoin_new(new_str, &temp);
            start = *j;
            handle_dolar_double(str, new_str, j);
            start = *j;
        }
        (*j)++;
    }
    //ft_strjoin_new(&new_str, &temp);
}

static void handle_dolar_alone(char *str, char **new_str, int *j)
{
    char    *temp;
    int     start;

    (*j)++;
    start = *j;
    if (str[*j] == 0 || (ft_isalpha(str[*j]) == 0 && str[*j] != '_' && str[*j] != '\'' && str[*j] != '"'))
    {
        temp = ft_strdup("$");
        ft_strjoin_new(new_str, &temp);
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
    ft_strjoin_new(new_str, &temp);
}

static void no_quotes(char *str, char **new_str, int *j)
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
        ft_strjoin_new(new_str, &temp);
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
    new_str = NULL;
    printf("1\n"); //test
    while ((*d)->args[i])
    {
        if (is_inside_quotes((*d)->args[i], 0, ft_strlen((*d)->args[i])) == -1)
        {
            printf("2\n"); //test
            //error open quotes
            exit(EXIT_FAILURE);
        }
        printf("3\n"); //test
        j = 0;
        while ((*d)->args[i][j] != 0)
        {
            printf("4\n"); //test
            if ((*d)->args[i][j] == '\'')
                single_quote((*d)->args[i], &new_str, &j);
            printf("5\n"); //test
            if ((*d)->args[i][j] == '"')
            {
                printf("6\n"); //test
                double_quote((*d)->args[i], &new_str, &j);
            }
            else
            {
                printf("7\n"); //test
                no_quotes((*d)->args[i], &new_str, &j);
            }
            printf("8\n"); //test
            //j++;
        }
        printf("9\n"); //test
        free((*d)->args[i]);
        printf("10\n"); //test
        (*d)->args[i] = ft_strdup(new_str);
        printf("11\n"); //test
        free(new_str);
        printf("12\n"); //test
        i++;
    }
}