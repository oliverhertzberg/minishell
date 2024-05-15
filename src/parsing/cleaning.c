#include "../../headers/minishell.h"

static void clean_cmd(t_cmd_data **d)
{
    ft_strip((*d)->args[0]);
    if (check_word((*d)->args[0], 0, ft_strlen((*d)->args[0])) == 2)
        ft_skip((*d)->args[0]);
    if (inside_mix((*d)->args[0], 0, ft_strlen((*d)->args[0])) == 1
        || inside_mix((*d)->args[0], 0, ft_strlen((*d)->args[0])) == 2)
        ft_skip_fl(&((*d)->args[0]));
}
/*
error if quote is not closed
cleaning if entire string is inside of pair of quotes and memorising which quotes were there
*/
void    clean_quotes(t_cmd_data **d)
{
    int i;

    i = 1;
    clean_cmd(d);
    while ((*d)->args[i])
    {
        ft_strip((*d)->args[i]);
        //if open and not closed
        if (check_word((*d)->args[i], 0, ft_strlen((*d)->args[0])) == 0)
        {
            //error open quote
            exit(1);
        }
        // if open and closed (we are cleaning only if entire string is inside of quotes)
        else if (check_word((*d)->args[i], 0, ft_strlen((*d)->args[0])) == 2)
        {
            if (is_inside_quotes((*d)->args[i], 0, ft_strlen((*d)->args[0])) == 1)
            {
                (*d)->quote[i] = 2;
                ft_skip_fl(&((*d)->args[i]));
            }
            else if (is_inside_quotes((*d)->args[i], 0, ft_strlen((*d)->args[0])) == 2)
            {
                (*d)->quote[i] = 1;
                ft_skip_fl(&((*d)->args[i]));
            }
        }
        // if inside of quotes we have different quotes
        else if (check_word((*d)->args[i], 0, ft_strlen((*d)->args[0])) == 1)
        {
            if (is_inside_quotes((*d)->args[i], 0, ft_strlen((*d)->args[0])) == 1)
            {
                (*d)->quote[i] = 2;
                ft_skip_fl(&((*d)->args[i]));
            }
            else if (is_inside_quotes((*d)->args[i], 0, ft_strlen((*d)->args[0])) == 2)
            {
                (*d)->quote[i] = 1;
                ft_skip_fl(&((*d)->args[i]));
            }
        }
        i++;
    }
}