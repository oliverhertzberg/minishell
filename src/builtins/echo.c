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
