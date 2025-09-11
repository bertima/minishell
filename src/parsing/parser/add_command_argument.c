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
	*command = ft_calloc(1, sizeof(t_command));
	if (!*command)
		return (1);
	(*command)->arg = ft_calloc(1, sizeof(char *));
	if (!(*command)->arg)
	{
		free(*command);
		return (1);
	}
	return (0);
}

int	add_command(t_shell *shell, t_command **command)
{
	t_command	*temp_command;

	temp_command = shell->command;
	if (!shell->command)
	{
		if (new_command(&shell->command))
			return (1);
		*command = shell->command;
		return (0);
	}
	while (temp_command->next)
		temp_command = temp_command->next;
	if (new_command(&temp_command->next))
		return (1);
	*command = temp_command->next;
	return (0);
}

static int	creat_first(t_command *command, char *new)
{
	command->arg = ft_calloc(1, sizeof(char *));
	if (!command->arg)
	{
		free(command);
		return (1);
	}
	command->arg[0] = new;
	return (0);
}

static int	init_data(char **new, t_command *c, t_token *temp, char ***new_a)
{
	int	last;

	last = 0;
	*new = ft_strdup(temp->sentence);
	if (!*new)
		return (1);
	last = ft_len_double_char(c->arg);
	*new_a = ft_calloc(last + 2, sizeof(char *));
	if (!*new_a)
	{
		free(*new);
		return (1);
	}
	return (0);
}

int	add_arg(t_command *command, t_token *temp, int i)
{
	char	*new;
	char	**new_a;

	new = NULL;
	new_a = NULL;
	if (init_data(&new, command, temp, &new_a))
		return (1);
	if (!command->arg)
	{
		if (creat_first(command, new))
			return (1);
		return (0);
	}
	while (command->arg[i])
	{
		new_a[i] = ft_strdup(command->arg[i]);
		if (!new_a[i])
			return (1);
		i++;
	}
	ft_free_split(command->arg);
	new_a[i] = new;
	new_a[i + 1] = NULL;
	command->arg = new_a;
	return (0);
}
