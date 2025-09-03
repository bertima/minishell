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
	if (!temp->next->token)
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
		minishell->token->token = ft_substr(minishell->line, i, j);
		if (!minishell->token->token)
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
	line = minishell->line;
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
	*i += j;
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
		}
		while (line[start + len] && !ft_isspace(line[start + len])
			&& line[start + len] != '\'' && line[start + len] != '\"')
			len++;
		if (len > 0)
		{
			if (add_token(minishell, start, len))
				return (1);
			start += len;
		}
		else
			start++;
	}
	return (0);
}

int	tokening(t_minishell *minishell)
{
	if (divide(minishell, minishell->line, 0, 0))
		return (1);
//peut peut etre creer des probleme test : echo "'"coucou"'"
//	if (search_quote(minishell))
//		return (1);
//	t_token *temp = minishell->token;
//	int i = 1;
//	while (minishell->token)
//	{
//		temp = temp->next;
//		printf("%s: token %d\n", minishell->token->token, i);
//		if (minishell->token->token)
//			free(minishell->token->token);
//		if (minishell->token)
//			free(minishell->token);
//		i++;
//		minishell->token = temp;
//	}
	return (0);
}
