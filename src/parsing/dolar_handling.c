#include "../../headers/minishell.h"

static void dollar_cleaning_dq(char *str, char **new_str, int *j, t_hmap **h)
{
    char    *temp;
    int     start;
    char    *value;

    (*j)++;
    temp = NULL;
    if (str[*j] == 0 || str[*j] == '\'' || str[*j] == '"'
        || (ft_isalpha(str[*j]) == 0 && str[*j] != '_'
        && ft_isdigit(str[*j]) == 0))
    {
        temp = ft_strdup("$");
        *new_str = ft_strjoin_new(new_str, &temp);
        free(temp);
    }
    else if (ft_isdigit(str[*j]) == 1)
        (*j)++;
    else
    {
        start = *j;
        while (str[*j] != 0 && str[*j] != '\'' && str[*j] != '"'
            && ((ft_isalpha(str[*j]) == 1 || str[*j] == '_'
            || ft_isdigit(str[*j]) == 1)))
            (*j)++;
        temp = ft_substr(str, start, *j - start);
        if (return_value_hash(*h, temp) != NULL)
        {
            value = ft_strdup(return_value_hash(*h, temp));
            free(temp);
            *new_str = ft_strjoin_new(new_str, &value);
            free(value);
        }
    }
}

static void dollar_cleaning_nq(char *str, char **new_str, int *j, t_hmap **h)
{
    char    *temp;
    int     start;
    char    *value;

    (*j)++;
    temp = NULL;
    if (str[*j] == 0 || (ft_isalpha(str[*j]) == 0 && str[*j] != '_'
        && ft_isdigit(str[*j]) == 0 && str[*j] != '\'' && str[*j] != '"'))
    {
        temp = ft_strdup("$");
        *new_str = ft_strjoin_new(new_str, &temp);
        free(temp);
    }
    else if (str[*j] == '\'' || str[*j] == '"')
        return ;
    else if (ft_isdigit(str[*j]) == 1)
        (*j)++;
    else
    {
        start = *j;
        while (str[*j] != 0 && str[*j] != '\'' && str[*j] != '"'
            && ((ft_isalpha(str[*j]) == 1 || str[*j] == '_'
            || ft_isdigit(str[*j]) == 1)))
            (*j)++;
        temp = ft_substr(str, start, *j - start);
        if (return_value_hash(*h, temp) != NULL)
        {
            value = ft_strdup(return_value_hash(*h, temp));
            free(temp);
            *new_str = ft_strjoin_new(new_str, &value);
            free(value);
        }
    }
}

static char *single_quotes(char *str, int *j)
{
    char    *new_str;
    int     start;

    start = *j;
    while (str[*j] != 0 && str[*j] != '\'')
        (*j)++;
    new_str = ft_substr(str, start, *j - start);
    return (new_str);
}

static char *double_quotes(char *str, int *j, t_hmap **h, int exit_code)
{
    char    *new_str;
    char    *temp;
    int     start;

    new_str = NULL;
    while (str[*j] != 0 && str[*j] != '"')
    {
        temp = NULL;
        if (str[*j] != '$')
        {
            start = *j;
            while(str[*j] != 0 && str[*j] != '"' && str[*j] != '$')
                (*j)++;
            temp = ft_substr(str, start, *j - start);
            new_str = ft_strjoin_new(&new_str, &temp);
        }
        if (str[*j] == '$')
        {
            if (str[*j + 1] == '?')
            {
                temp = ft_strdup(ft_itoa(exit_code));
                new_str = ft_strjoin_new(&new_str, &temp);
                (*j) += 2;
            }
            else
                dollar_cleaning_dq(str, &new_str, j, h);
        }
        if (temp != NULL)
            free(temp);
    }
    return (new_str);
}

static char *no_quotes(char *str, int *j, t_hmap **h, int exit_code)
{
    char    *new_str;
    char    *temp;
    int     start;

    new_str = NULL;
    while (str[*j] != 0 && str[*j] != '"' && str[*j] != '\'')
    {
        temp = NULL;
        if (str[*j] != '$')
        {
            start = *j;
            while(str[*j] != 0 && str[*j] != '"' && str[*j] != '\'' && str[*j] != '$')
                (*j)++;
            temp = ft_substr(str, start, *j - start);
            new_str = ft_strjoin_new(&new_str, &temp);
        }
        if (str[*j] == '$')
        {
            if (str[*j + 1] == '?')
            {
                temp = ft_strdup(ft_itoa(exit_code));
                new_str = ft_strjoin_new(&new_str, &temp);
                (*j) += 2;
            }
            else
            dollar_cleaning_nq(str, &new_str, j, h);
        }
        if (temp != NULL)
            free(temp);
    }
    return (new_str);
}

void    clean_dolar(char **str, t_hmap  **h, int exit_code)
{
    int     i;
    int     j;
    char    *new_str;
    char    *temp;
    char    *temp1;

    i = 0;
    while (str[i] != NULL)
    {
        new_str = NULL;
        temp = NULL;
        temp1 = NULL;
        if (check_word(str[i], 0, ft_strlen(str[i])) == 0)
            // open quotes error
            exit(EXIT_FAILURE);
        if (is_in_str(str[i], '\'', 0, ft_strlen(str[i])) == -1
            && is_in_str(str[i], '"', 0, ft_strlen(str[i])) == -1
            && is_in_str(str[i], '$', 0, ft_strlen(str[i])) == -1)
            i++;
        else
        {
            j = 0;
            while (str[i][j])
            {
                if (str[i][j] == '\'')
                {
                    j++;
                    temp = single_quotes(str[i], &j);
                    new_str = ft_strjoin_new(&new_str, &temp);
                    free(temp);
                    j++;
                }
                else if (str[i][j] == '"')
                {
                    j++;
                    temp = double_quotes(str[i], &j, h, exit_code);
                    new_str = ft_strjoin_new(&new_str, &temp);
                    free(temp);
                    j++;
                }
                else
                {
                    temp = no_quotes(str[i], &j, h, exit_code);
                    new_str = ft_strjoin_new(&new_str, &temp);
                    free(temp);
                }
            }
            free(str[i]);
            str[i] = ft_strdup(new_str);
            free(new_str);
            i++;
        }
    }
}