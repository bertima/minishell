/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:58:20 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/04 11:36:52 by bertrmar         ###   ########.fr       */
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
	temp->next->sentence = ft_substr(minishell->data->line, i, j);
	if (!temp->next->sentence)
		return (1);
	return (0);
}

static int	add_token(t_minishell *minishell, int i, int j)
{
	if (!minishell->token)
	{
		minishell->token = ft_calloc(1, sizeof(t_token));
		if (!minishell->token)
			return (1);
		minishell->token->sentence = ft_substr(minishell->data->line, i, j);
		if (!minishell->token->sentence)
			return (1);
	}
	else
	{
		if (add_back_token(minishell, i, j))
			return (1);
	}
	return (0);
}

static int	find_quote(t_minishell *minishell, int *i, int len, char c)
{
	int		j;
	char	*line;

	j = 1;
	line = minishell->data->line;
	while (line[*i + j] && line[*i + j] != c)
		j++;
	while (line[*i + j] && line[*i + j] != '\''
		&& line[*i + j] != '\"' && !ft_isspace(line[*i + j]))
		j++;
	if (!line[*i + j])
		return (1);
	len += j + 1;
	if (add_token(minishell, *i, len))
		return (1);
	*i += j + 1;
	return (0);
}

static int	divide(t_minishell *minishell, char *line, int start, int len)
{
	while (line[start])
	{
		len = 0;
		while (line[start] && ft_isspace(line[start]))
			start++;
		if (!line[start])
			break ;
		if (line[start] == '\'' || line[start] == '\"')
		{
			if (find_quote(minishell, &start, 0, line[start]))
				return (return_err_int(minishell, "Quote no close !"));
			continue ;
		}
		while (line[start + len] && !ft_isspace(line[start + len])
			&& line[start + len] != '\'' && line[start + len] != '"')
			len++;
		if (len > 0)
		{
			if (add_token(minishell, start, len))
				return (1);
			start += len;
		}
	}
	return (0);
}

int	tokening(t_minishell *minishell)
{
	if (divide(minishell, minishell->data->line, 0, 0))
		return (1);
	return (0);
}
