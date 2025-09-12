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

int	remove_quote(t_shell *shell, t_command *command, int i, int *j)
{
	if (command->arg[i][*j] == '\'' || command->arg[i][*j] == '\"')
	{
		if (command->arg[i][*j] == '\'')
		{
			if (single_quote(command, j, i))
				return (1);
		}
		else
		{
			if (double_quote(shell, command, j, i))
				return (1);
		}
	}
	return (0);
}
