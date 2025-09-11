/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 09:34:55 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/28 16:10:42 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_data_builtin(t_shell *shell)
{
	if (shell->data->env)
		ft_free_split(shell->data->env);
	if (shell->data->line)
		free(shell->data->line);
	return ;
}

static void	free_redir(t_redir **redir)
{
	t_redir	*temp;

	while (*redir)
	{
		temp = (*redir)->next;
		if ((*redir)->file)
			free((*redir)->file);
		*redir = temp;
	}
}

void	free_command_redir_token(t_shell *shell)
{
	t_token		*temp;
	t_command	*temp_c;

	while (shell->token)
	{
		temp = shell->token->next;
		if (shell->token->sentence)
			free(shell->token->sentence);
		free(shell->token);
		shell->token = temp;
	}
	while (shell->command)
	{
		temp_c = shell->command->next;
		if (shell->command->arg)
			ft_free_split(shell->command->arg);
		if (shell->command->redir)
			free_redir(&shell->command->redir);
		free(shell->command);
		shell->command = temp_c;
	}
}

void	all_free(t_shell *shell)
{
	if (!shell)
		return ;
	free_command_redir_token(shell);
	free_data_builtin(shell);
}
