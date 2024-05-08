#include "../../headers/builtins.h"

static void unset_oldpwd(t_hmap **h)
{
    if (return_value_hash(*h, "OLDPWD"))
        remove_var(h, "OLDPWD");
}

void    add_shelllevel(t_hmap	**hashmap)
{
    char    *temp;
    t_hmap  *h_temp;
    int     shlvl;

    temp = return_value_hash(*hashmap, "SHLVL");
    shlvl = ft_atoi_short(temp);
    if (shlvl < 0)
        shlvl = 0;
    free(temp);
    h_temp = get_value_hmap(hashmap, "SHLVL");
    change_value(hashmap, "SHLVL", ft_itoa(shlvl + 1));
    unset_oldpwd(&h_temp); //check this!
}