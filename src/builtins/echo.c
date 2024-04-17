/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:06:56 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/16 15:18:23 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"

static int	is_substr(char *str, char *sub)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != 0)
	{
		j = 0;
		if (str[i] == sub[0])
		{
			while (sub[j] != 0 && sub[j] == str[i])
			{
				i++;
				j++;
			}
			if (sub[j] == 0)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

/* we should change it to work with export and unset also!
 * this is doing the simpest stuff, with just printing string and 
 * with option -n, but not if we have some variable set with export!  */
void	ft_echo(char *input)
{
	if (is_substr(input, "-n") == 1)
		printf("%s", input + 8);
	else
		printf("%s\n", input + 5);
}
