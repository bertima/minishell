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

static int	calcul_len_var_split(t_shell *shell)
{
	int	start;
	int	len;
	int	end;
	int	i;

	i = ft_strlen(shell->data->var_value);
	len = 0;
	if (i == 0)
		return (len);
	while (shell->data->var_value[i] == '\0'
		|| ft_isspace(shell->data->var_value[i]) == 1)
		i--;
	while (i > 0 && ft_isspace(shell->data->var_value[i]) == 0)
		i--;
	i++;
	start = i;
	while (ft_isspace(shell->data->var_value[i]) == 0
		&& shell->data->var_value[i])
		i++;
	end = i;
	len = end - start;
	return (len);
}

static int	word_split(t_shell *shell, char ***arg, int *i, int *start_end)
{
	int	j;

	j = start_end[0];
	if (!(*arg)[*i] || !(*arg)[*i][0])
		return (suppress_arg(shell, arg, i));
	while ((*arg) && (*arg)[*i] && (*arg)[*i][j] && j < start_end[1])
	{
		while ((*arg)[*i][j])
			j++;
		start_end[1] = j;
		if (start_end[1] > start_end[0])
		{
			if (insert_arg_expand(arg, start_end, i))
				return (1);
			start_end[1] = calcul_len_var_split(shell);
			j = start_end[1];
		}
	}
	return (0);
}

int	expand_in_arg(t_shell *shell, char ***arg, int *i, int *j)
{
	int			start_end[2];

	shell->data->stock = *i;
	while (*arg && (*arg)[*i] && (*arg)[*i][*j])
	{
		shell->data->result = quote_handler(shell, arg, i, j);
		if (shell->data->result == 1)
			return (1);
		if (shell->data->result == 2)
			continue ;
		start_end[0] = *j;
		shell->data->result = expand_without_quote(shell, arg, i, j);
		if (shell->data->result == 1)
			return (1);
		if (shell->data->result == 2)
		{
			start_end[1] = *j;
			if (word_split(shell, arg, i, start_end))
				return (1);
			*j = start_end[1];
			continue ;
		}
		(*j)++;
	}
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
