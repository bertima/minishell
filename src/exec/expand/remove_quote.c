/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:48:59 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/09 11:20:07 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	delete_quote(t_command *command, int index)
{
	char	*temp;
	int		i;

	temp = malloc(sizeof(char) * (ft_strlen(command->arg[index]) - 1));
	if (!temp)
		return (1);
	i = 0;
	while (i < ((int)ft_strlen(command->arg[index]) - 2))
	{
		temp[i] = command->arg[index][i + 1];
		i++;
	}
	temp[i] = '\0';
	free(command->arg[index]);
	command->arg[index] = temp;
	return (0);
}

int	remove_quote(t_command *command, int i)
{
	t_command	*temp;

	temp = command;
	while (temp)
	{
		i = 0;
		while (temp->arg && temp->arg[i])
		{
			if (temp->arg[i][0] == '\'' || temp->arg[i][0] == '\"')
			{
				if (delete_quote(temp, i))
					return (1);
			}
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
