/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokening.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:58:20 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/28 16:16:13 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_back_token(t_minishell *minishell, int i, int j)
{
	t_token	*temp;

	temp = minishell->token;
	while (temp->next)
		temp = temp->next;
	temp->next = ft_calloc(1, sizeof(t_token));
	if (!temp->next)
		return (1);
	temp->next->token = ft_substr(minishell->line, i, j);
	if (!minishell->token->token)
		return (1);
	temp->next->next = NULL;
	return (0);
}

static int	add_token(t_minishell *minishell, int i, int j)
{
	if (!minishell->token)
	{
		minishell->token = ft_calloc(1, sizeof(t_token));
		if (!minishell->token)
			return (1);
		minishell->token->token = ft_substr(minishell->line, i, j);
		if (!minishell->token->token)
			return (1);
		minishell->token->next = NULL;
	}
	else
	{
		if (add_back_token(minishell, i, j))
			return (1);
	}
	return (0);
}

static int	find_quote(t_minishell *minishell, int *i, int *j)
{
	if (minishell->line[*i] == '\'')
	{
		while (minishell->line[*i + *j] && minishell->line[*i + *j] != '\'')
			j++;
		if (minishell->line[*i + *j] != '\'')
			return (1);
		add_token(minishell, *i, *j);
		*i += *j;
	}
	else if (minishell->line[*i] == '\"')
	{
		while (minishell->line[*i + *j] && minishell->line[*i + *j] != '\"')
			j++;
		if (minishell->line[*i + *j] != '\"')
			return (1);
		*i += *j;
	}
	return (0);
}

static int	divide(t_minishell *minishell)
{
	int	i;
	int	j;

	i = 0;
	while (minishell->line[i])
	{
		j = 0;
		while (ft_isspace(minishell->line[i]))
			i++;
		if (minishell->line[i] == '\"' || minishell->line[i] == '\'')
		{
			if (find_quote(minishell, &i, &j))
				return (1);
		}
		while (minishell->line[i + j]
			&& ft_isspace(minishell->line[i + j]) == 0)
			j++;
		add_token(minishell, i, j);
		i += j;
	}
	return (0);
}

int	tokening(t_minishell *minishell)
{
	if (search_quote(minishell))
		return (1);
	if (divide(minishell))
		return (1);
	return (0);
}
