#include "../../headers/minishell.h"

t_cmd_data *get_node_in_use(t_cmd_data **lst)
{
    t_cmd_data *current;
    t_cmd_data *node_in_use;

    current = *lst;
    if (current->in_use == 1)
    {
        *lst = current->next;
        return (current);
    }
    while (current)
    {
        if (current->next->in_use == 1)
        {
            node_in_use = current->next;
            current->next = current->next->next;
        }
        current = current->next;
    }
}
