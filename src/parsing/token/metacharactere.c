/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharactere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:15:25 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/10 13:33:24 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	metachar(char *line, int index)
{
	int	i;

	i = 0;
	while (line[index + i] == '<' || line[index + i] == '>'
		|| line[index + i] == '|')
	{
        if (line[index + i] == '|')
            return (1);
		i++;
	}
	return (i);
}
