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

static int	verif_quote(char *str, int i, int count_d, int count_s)
{
	while (str && str[i])
	{
		if (str[i] == '\'' && !count_s)
			count_s = 1;
		else if (str[i] == '\"' && !count_d && !count_s)
			count_d = 1;
		else if (str[i] == '\'' && count_s)
			count_s = 0;
		else if (str[i] == '\"' && count_d && !count_s)
			count_d = 0;
		i++;
	}
	if (count_d || count_s)
		return (1);
	return (0);
}

int	search_quote(t_minishell *minishell)
{
	t_token	*temp;

	temp = minishell->token;
	while (temp)
	{
		if (verif_quote(temp->token, 0, 0, 0))
		{
			ft_putstr_fd("Quote no close searc_quote file quote !\n", 2);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	find_quote(char *line, int start, int *len, char c)
{
	int	j;

	j = 1;
	while (line[start + j] && line[start + j] != c)
		j++;
	if (!line[start + j])
		return (1);
	*len += j + 1;
	return (0);
}
