#include "../../headers/minishell.h"

void	init_quote(t_cmd_data **d)
{
	int	i;

	i = 0;
	(*d)->quote = (int *)malloc((*d)->arg_count * sizeof(int));
	if (!((*d)->quote))
        //error
		exit(1);
	while (i < (*d)->arg_count)
	{
		(*d)->quote[i] = 0;
	i++;
	}
}

/*
cleaning first command
*/
static void	clean_cmd(t_cmd_data **d)
{
	ft_strip(&(*d)->args[0]);
	if (check_word((*d)->args[0], 0, ft_strlen((*d)->args[0])) == 2)
		ft_skip((*d)->args[0]);
	if (inside_mix((*d)->args[0], 0, ft_strlen((*d)->args[0])) == 1
		|| inside_mix((*d)->args[0], 0, ft_strlen((*d)->args[0])) == 2)
		ft_skip_fl(&((*d)->args[0]));
}

static void	clean_outside(t_cmd_data **d, int *i)
{
    //if open and not closed
	if (check_word((*d)->args[*i], 0, ft_strlen((*d)->args[*i])) == 0)
	{
        //error open quote
		exit(1);
	}
    // if open and closed (we are cleaning only if entire string is inside of quotes)
    // or if inside of quotes we have different quotes
	if (check_word((*d)->args[*i], 0, ft_strlen((*d)->args[*i])) == 2
		|| check_word((*d)->args[*i], 0, ft_strlen((*d)->args[*i])) == 1)
	{
		if (is_inside_quotes((*d)->args[*i], 0, ft_strlen((*d)->args[*i])) == 1)
		{
			(*d)->quote[*i] = 2;
			ft_skip_fl(&((*d)->args[*i]));
		}
		else if (is_inside_quotes((*d)->args[*i], 0, ft_strlen((*d)->args[*i])) == 2)
		{
			(*d)->quote[*i] = 1;
			ft_skip_fl(&((*d)->args[*i]));
		}
	}
}

/*
error if quote is not closed
cleaning if entire string is inside of pair of quotes and memorising which quotes were there
*/
void	clean_quotes(t_cmd_data **d)
{
	int	i;

	i = 1;
	clean_cmd(d);
	while ((*d)->args[i])
	{
		ft_strip(&(*d)->args[i]);
		clean_outside(d, &i);
		i++;
	}
}
