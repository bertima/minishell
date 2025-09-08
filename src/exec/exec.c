/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:22:26 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/04 11:40:24 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_minishell *minishell)
{
	if (expand(minishell, minishell->command, 0, 0))
		return (1);
	while (minishell->command)
	{
		if (minishell->command->arg)
		{
			if (ft_strcmp(minishell->command->arg[0], "echo") == 0)
				echo(minishell->command->arg);
			if (ft_strcmp(minishell->command->arg[0], "env") == 0)
				show_environ(minishell->data->env);
		}
		minishell->command = minishell->command->next;
	}
	return (0);
}
