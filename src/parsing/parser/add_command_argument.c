/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command_argument.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:57:14 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/04 10:02:26 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_command(t_command **command)
{
	*command = calloc(1, sizeof(t_command));
	if (!*command)
		return (1);
	return (0);
}

int	add_command(t_minishell *minishell, t_command **current)
{
	t_command	*temp_command;

	temp_command = minishell->command;
	if (!minishell->command)
	{
		if (new_command(&minishell->command))
			return (1);
		*current = minishell->command;
		return (0);
	}
	while (temp_command->next)
		temp_command = temp_command->next;
	if (new_command(&temp_command->next))
		return (1);
	*current = temp_command->next;
	return (0);
}

int	add_arg(t_command *current, t_token *temp, int nbr_arg)
{
	t_token	**more_arg;

	more_arg = realloc(current->arg, (nbr_arg + 2) * sizeof(t_token *));
	if (!more_arg)
		return (1);
	current->arg = more_arg;
	current->arg[nbr_arg] = temp;
	current->arg[nbr_arg + 1] = NULL;
	current->nbr_arg++;
	return (0);
}
