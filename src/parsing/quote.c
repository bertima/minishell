/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:56:57 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/27 15:45:46 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_double_quote(t_traitement *traitement)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (traitement->line[i])
	{
		if (traitement->line[i] == '\"' && count == 1)
			count--;
		if (traitement->line[i] == '\"' && count == 0)
			count++;
		if (count > 1 || count < 0)
			return (1);
		i++;
	}
	if (count == 1)
		return (1);
	return (0);
}

static int	search_simple_quote(t_traitement *traitement)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (traitement->line[i])
	{
		if (traitement->line[i] == '\'' && count == 1)
			count--;
		if (traitement->line[i] == '\'' && count == 0)
			count++;
		if (count > 1 || count < 0)
			return (1);
		i++;
	}
	if (count == 1)
		return (1);
	return (0);
}

int	search_quote(t_traitement *traitement)
{
	char	*line;

	line = traitement->line;
	if (search_double_quote(traitement) || search_simple_quote(traitement))
		return (1);
	return (0);
}
