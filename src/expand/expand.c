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

char	*search_name(char *str, int start)
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

static int	loop(t_shell *shell, t_command *command, int i, int j)
{
	int		result;
	char	*name;

	while (command->arg && command->arg[i] && command->arg[i][j])
	{
		if (command->arg[i][j] == '\'' || command->arg[i][j] == '\"')
		{
			if (remove_quote(shell, command, i, &j))
				return (1);
		}
		if (command->arg[i][j] == '$')
		{
			name = search_name(command->arg[i], j + 1);
			if (name)
			{
				result = var_exist(shell, &command->arg[i], j, &name);
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

int	expand(t_shell *shell, t_command *command, int i, int j)
{
	t_command	*temp;

	temp = command;
	while (temp)
	{
		i = 0;
		while (temp->arg && temp->arg[i])
		{
			j = 0;
			if (loop(shell, temp, i, j))
				return (1);
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
