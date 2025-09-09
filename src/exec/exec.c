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

int	exec(t_minishell *minishell)
{
	t_command	*command;

	if (expand(minishell, minishell->command, 0, 0))
		return (1);
	if (remove_quote(minishell->command, 0))
		return (1);
	command = minishell->command;
	while (command)
	{
		if (command->arg)
		{
			if (ft_strcmp(minishell->command->arg[0], "echo") == 0)
				echo(minishell->command->arg);
			if (ft_strcmp(minishell->command->arg[0], "env") == 0)
				show_environ(minishell->data->env);
		}
		command = command->next;
	}
	command = minishell->command;
	show_commands(minishell->command, 0, 1);
	return (0);
}
