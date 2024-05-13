#include "../../headers/minishell.h"


//not done
void    clean_quotes(t_cmd_data **d)
{
    int i;

    i = 0;
    while ((*d)->args[i])
    {
        ft_strip((*d)->args[i]);
        if (check_word((*d)->args[i]) == 0)
        {
            //error open quote
            exit(1);
        }
        else if (check_word((*d)->args[i]) == 2) //skipping useless quotes
            ft_skip((*d)->args[i]);

        i++;
    }
}