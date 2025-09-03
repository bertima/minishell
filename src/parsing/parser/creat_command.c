/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:28:02 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/03 12:28:15 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_command_back(t_command *command)
{
	command = calloc(1, sizeof(t_command *));
	if (!command)
		return (1);
    return (0);
}

static int	add_command(t_minishell *minishell, t_command *current)
{
	t_command	*temp_command;

	temp_command = minishell->command;
	if (!temp_command)
	{
		if (new_command_back(temp_command))
			return (1);
		current = temp_command;
		return (0);
	}
	while (temp_command->next)
		temp_command = temp_command->next;
	if (new_command_back(temp_command->next))
		return (1);
	current = temp_command->next;
    current->next = NULL;
	return (0);
}

static void  add_arg(t_command *current, t_token *temp, int nbr_arg)
{
    t_token **list;

    list = current->arg;
    if (!list[0])
        list[0] = temp;
    else
    {
        list[nbr_arg] = temp;
        list[nbr_arg + 1] = NULL;
    }
} 

static int  compare(t_minishell *minishell, t_command *current, t_token *temp)
{
    if (!current || temp->type == PIPE)
    {
        if (add_command(minishell, current))
            return (1);
    }
    else if (temp->type != WORD)
    {
        if (redirect(current, temp))
            return (1);
    }
    else
    {
        add_arg(current, temp, current->nbr_arg);
         current->nbr_arg++;
    }
    return (0);
}

int creat_command(t_minishell *minishell)
{
	t_command	*current;
    t_token     *temp;

    temp = minishell->token;
    current = NULL;
	while (temp)
	{
        if (compare(minishell, current, temp))
            return (1);
		temp = temp->next;
	}
    return (0);
}