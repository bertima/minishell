/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:24:23 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:24:25 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_remove_quote(char ***arg, int stock, int i)
{
	int	j;

	j = 0;
	while (*arg && (*arg)[stock] && stock <= i)
	{
		j = 0;
		while ((*arg)[stock] && (*arg)[stock][j])
		{
			if ((*arg)[stock][j] == '\"' || (*arg)[stock][j] == '\'')
			{
				if (remove_quote_expand(&(*arg)[stock], &j))
					return (1);
			}
			else
				j++;
		}
		stock++;
	}
	return (0);
}

static int	skip_quote(char **arg, int *start_end, int i, int *j)
{
	char	quote;

	if (arg[i][*j] == '\'' || arg[i][*j] == '"')
	{
		quote = arg[i][*j];
		(*j)++;
		while (arg[i][*j] && arg[i][*j] != quote)
			(*j)++;
		(*j)++;
		start_end[0] = *j;
		return (1);
	}
	return (0);
}

static int	word_split(char ***arg, int *i, int j)
{
	int		start_end[2];

	start_end[0] = 0;
	start_end[1] = 0;
	if (!(*arg)[*i] || !(*arg)[*i][0])
		return (suppress_arg(arg, i));
	while ((*arg) && (*arg)[*i] && (*arg)[*i][j])
	{
		if (skip_quote(*arg, start_end, *i, &j))
			continue ;
		while ((*arg)[*i][j] && (*arg)[*i][j] != '\'' && (*arg)[*i][j] != '\"')
			j++;
		start_end[1] = j;
		if (start_end[1] > start_end[0])
		{
			if (insert_arg_expand(arg, start_end, i, &j))
				return (1);
			continue ;
		}
	}
	return (0);
}

int	expand_in_arg(t_shell *shell, char ***arg, int *i, int *j)
{
	int			result;
	int			stock;

	stock = *i;
	while (*arg && (*arg)[*i] && (*arg)[*i][*j])
	{
		result = quote_handler(shell, arg, i, j);
		if (result == 1)
			return (1);
		if (result == 2)
			continue ;
		result = expand_without_quote(shell, arg, i, j);
		if (result == 1)
			return (1);
		if (result == 2)
			continue ;
		(*j)++;
	}
	if (word_split(arg, i, 0))
		return (1);
	if (loop_remove_quote(arg, stock, *i))
		return (1);
	return (0);
}

int	expand(t_shell *shell, t_cmd *cmd, int i, int j)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		i = 0;
		while (temp->arg && temp->arg[i])
		{
			j = 0;
			if (expand_in_arg(shell, &temp->arg, &i, &j))
				return (1);
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
