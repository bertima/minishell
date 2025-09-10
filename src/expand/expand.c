/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:35:57 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/05 15:43:04 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_name(char *str, int start)
{
	int		len;
	char	*name;

	len = 0;
	while (ft_isalnum(str[start + len]))
		len++;
	name = ft_substr(str, start, len);
	if (!name)
		return (NULL);
	return (name);
}

static int	skip_arg(t_minishell *minishell, char *arg, int *j)
{
	*j += 1;
	while (arg[*j])
	{
		if (arg[*j] == '\'')
			return (0);
		(*j)++;
	}
	return (return_err_int(minishell, "Quote no close !\n"));
}

static int	loop(t_minishell *minishell, t_command *command, int i, int j)
{
	char		*name;
	int			result;
	int			stop;

	while (command->arg && command->arg[i] && command->arg[i][j])
	{
		if (command->arg[i][j] == '\"' && stop == 0)
			stop = 1;
		else if (command->arg[i][j] == '\"' && stop == 1)
			stop = 0;
		if (command->arg[i][j] == '\'' && stop == 0)
		{
			if (skip_arg(minishell, command->arg[i], &j))
				return (1);
		}
		if (command->arg[i][j] == '$')
		{
			name = search_name(command->arg[i], j + 1);
			if (name)
			{
				result = var_exist(minishell, &command->arg[i], j, &name);
				if (result == 1)
					return (1);
				else if (result == 2)
					continue ;
			}
		}
		j++;
	}
	return (0);
}

int	expand(t_minishell *minishell, t_command *command, int i, int j)
{
	t_command	*temp;

	temp = command;
	while (temp)
	{
		i = 0;
		while (temp->arg && temp->arg[i])
		{
			j = 0;
			if (loop(minishell, temp, i, j))
				return (1);
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
