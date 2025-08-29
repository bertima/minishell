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

static int	search_simple_quote(char *str);

static int	search_double_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"' && count == 1)
			count--;
		if (search_simple_quote(str))
			return (1);
		if (str[i] == '\"' && count == 0)
			count++;
		if (count > 1 || count < 0)
			return (1);
		i++;
	}
	if (count != 0)
		return (1);
	return (0);
}

static int	search_simple_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' && count == 1)
			count--;
		if (search_double_quote(str))
			return (1);
		if (str[i] == '\'' && count == 0)
			count++;
		if (count > 1 || count < 0)
			return (1);
		i++;
	}
	if (count != 0)
		return (1);
	return (0);
}

int	search_quote(t_minishell *minishell)
{
	t_token	*temp;

	temp = minishell->token;
	while (temp)
	{
		if (search_double_quote(temp->token)
			|| search_simple_quote(temp->token))
			return (1);
		temp = temp->next;
	}
	return (0);
}

// A voir si je conserve ce qu'il y a au dessus

static int	line_quoted(char *line, int *i, int *j, char c)
{
	if (line[*i] == c)
	{
		*j = *i + 1;
		if (line[*j] == '\0')
		{
			*j = 0;
			return (0);
		}
		while (line[*j] && line[*j] != c)
		{
			if (!line[*j])
				return (1);
			(*j)++;
		}
	}
	return (0);
}

int	find_quote(char *line, int *i, int *j)
{
	while (line[*i + *j])
	{
		if (line_quoted(line, i, j, '\''))
			return (1);
		else if (line_quoted(line, i, j, '\"'))
			return (1);
		else if (ft_isspace(line[*i + *j]))
			break ;
		(*j)++;
	}
	*i += *j;
	return (0);
}
