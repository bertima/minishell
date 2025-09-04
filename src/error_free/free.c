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

static void	free_cd(t_cd_memorie *cd)
{
	if (cd->before)
		free(cd->before);
	if (cd->now)
		free(cd->now);
}

static void	free_builtin(t_builtin *builtin)
{
	if (builtin->doc_here_in)
		free(builtin->doc_here_in);
	if (builtin->doc_here_out)
		free(builtin->doc_here_out);
	if (builtin->pipe)
		free(builtin->pipe);
	if (builtin->echo)
		free(builtin->echo);
}

void	free_command_token(t_command *command, t_token *token)
{
	t_token		*temp;
	t_command	*temp_c;

	while (token)
	{
		temp = token->next;
		if (token->sentence)
			free(token->sentence);
		free(token);
		token = temp;
	}
	while (command)
	{
		temp_c = command->next;
		free(command);
		command = temp_c;
	}
}

void	all_free(t_minishell *minishell)
{
	if (!minishell)
		return ;
	free_cd(minishell->memorie_cd);
	free_command_token(minishell->command, minishell->token);
	free_builtin(minishell->builtin);
	if (minishell->line)
		free(minishell->line);
}
