/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command_argument.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:27:31 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:27:32 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_command(t_cmd **cmd)
{
	*cmd = ft_calloc(1, sizeof(t_cmd));
	if (!*cmd)
		return (1);
	(*cmd)->arg = ft_calloc(1, sizeof(char *));
	if (!(*cmd)->arg)
	{
		free(*cmd);
		*cmd = NULL;
		return (1);
	}
	(*cmd)->fd_in = -1;
	(*cmd)->fd_out = -1;
	return (0);
}

int	add_command(t_shell *shell, t_cmd **cmd)
{
	t_cmd	*temp_command;

	temp_command = shell->cmd;
	if (!shell->cmd)
	{
		if (new_command(&shell->cmd))
			return (1);
		*cmd = shell->cmd;
		return (0);
	}
	while (temp_command->next)
		temp_command = temp_command->next;
	if (new_command(&temp_command->next))
		return (1);
	*cmd = temp_command->next;
	return (0);
}

static int	creat_first(t_cmd *cmd, char *new)
{
	cmd->arg = ft_calloc(1, sizeof(char *));
	if (!cmd->arg)
	{
		free(cmd);
		cmd = NULL;
		return (1);
	}
	cmd->arg[0] = new;
	return (0);
}

static int	init_data(char **new, t_cmd *cmd, t_token *temp, char ***new_a)
{
	int	last;

	last = 0;
	*new = ft_strdup(temp->sentence);
	if (!(*new))
		return (1);
	last = ft_len_array(cmd->arg);
	*new_a = ft_calloc(last + 2, sizeof(char *));
	if (!*new_a)
	{
		free(*new);
		*new = NULL;
		return (1);
	}
	return (0);
}

int	add_arg(t_cmd *cmd, t_token *temp, int i)
{
	char	*new;
	char	**new_a;

	new = NULL;
	new_a = NULL;
	if (init_data(&new, cmd, temp, &new_a))
		return (1);
	if (!cmd->arg)
	{
		if (creat_first(cmd, new))
			return (1);
		return (0);
	}
	while (cmd->arg[i])
	{
		new_a[i] = cmd->arg[i];
		i++;
	}
	free(cmd->arg);
	cmd->arg = NULL;
	new_a[i] = new;
	new_a[i + 1] = NULL;
	cmd->arg = new_a;
	return (0);
}
