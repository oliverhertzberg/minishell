#include "../../headers/minishell.h"

void    free_args(char **args, int arg_count)
{
    int i;

    i = 0;
    while (i < arg_count)
        free (args[i++]);
}
