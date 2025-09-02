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

static int	divide(t_minishell *minishell, char *line, int start, int len)
{
	while (line[start])
	{
		len = 0;
		while (line[start] && ft_isspace(line[start]))
			start++;
		if (!line[start])
			break ;
		while (line[start + len] && !ft_isspace(line[start + len]))
		{
			if (line[start + len] == '\'' || line[start + len] == '\"')
			{
				if (find_quote(line, start + len, &len, line[start + len]))
					return (return_err_int(minishell, "Quote no close tokening divide!"));
			}
			else
				len++;
		}
		if (add_token(minishell, start, len))
			return (return_err_int(minishell, "Error malloc divide file tokening!\n"));
		start += len;
	}
	return (0);
}

int	tokening(t_minishell *minishell)
{
	if (divide(minishell, minishell->line, 0, 0))
		return (1);
	if (search_quote(minishell))
		return (1);
	t_token *temp = minishell->token;
	int i = 1;
	while (minishell->token)
	{
		temp = temp->next;
		printf("%s: token %d\n", minishell->token->token, i);
		if (minishell->token->token)
			free(minishell->token->token);
		if (minishell->token)
			free(minishell->token);
		i++;
		minishell->token = temp;
	}
	return (0);
}
