/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:22:26 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/09 11:20:40 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_shell *shell)
{
	t_command	*command;

	if (expand(shell, shell->command, 0, 0))
		return (1);
	show_commands(shell->command, 0, 1);
	command = shell->command;
	while (command)
	{
		if (command->arg)
		{
			if (ft_strcmp(shell->command->arg[0], "echo") == 0)
				echo(shell->command->arg);
			if (ft_strcmp(shell->command->arg[0], "env") == 0)
				show_environ(shell->data->env);
		}
		command = command->next;
	}
	command = shell->command;
	return (0);
}
