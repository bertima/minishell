/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:27:12 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:27:13 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_back_token(t_shell *shell, int i, int j)
{
	t_token	*temp;

	temp = shell->token;
	while (temp->next)
		temp = temp->next;
	temp->next = ft_calloc(1, sizeof(t_token));
	if (!temp->next)
		return (1);
	temp->next->sentence = ft_substr(shell->data->line, i, j);
	if (!temp->next->sentence)
		return (1);
	return (0);
}

static int	add_token(t_shell *shell, int i, int j)
{
	if (!shell->token)
	{
		shell->token = ft_calloc(1, sizeof(t_token));
		if (!shell->token)
			return (1);
		shell->token->sentence = ft_substr(shell->data->line, i, j);
		if (!shell->token->sentence)
			return (1);
	}
	else
	{
		if (add_back_token(shell, i, j))
			return (1);
	}
	return (0);
}

static int	find_quote(t_shell *shell, char *line, int *len, char c)
{
	int	j;	

	j = 1;
	while (line[j] && line[j] != c)
		j++;
	if (!line[j])
		return (error_find_int(shell, QUOTE, 1, NULL));
	*len += j + 1;
	return (0);
}

static int	search_arg(t_shell *shell, char *line, int start, int *len)
{
	int	index;

	*len = 0;
	index = start;
	while (line[index] && !ft_isspace(line[index]))
	{
		if ((*len) > 0 && (line[index] == '|' || line[index] == '>'
				|| line[index] == '<'))
			break ;
		if (metachar(line, index, len))
			break ;
		if ((line[index] == '\'' || line[index] == '\"'))
		{
			if (find_quote(shell, &line[index], len, line[index]))
				return (1);
		}
		else
			(*len)++;
		index = start + *len;
	}
	return (0);
}

int	tokening(t_shell *shell)
{
	char	*line;
	int		start;
	int		len;

	start = 0;
	len = 0;
	line = shell->data->line;
	while (line[start])
	{
		while (line[start] && ft_isspace(line[start]))
			start++;
		if (!line[start])
			break ;
		if (search_arg(shell, line, start, &len))
			return (1);
		if (add_token(shell, start, len))
			return (error_find_int(shell, MALLOC, 1, NULL));
		start += len;
		len = 0;
	}
	return (0);
}
