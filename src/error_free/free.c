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

void	free_cd_cmd_token(t_cd_memorie *cd, t_token *token)
{
	t_token	*temp;

	if (cd->before)
		free(cd->before);
	if (cd->now)
		free(cd->now);
	while (token)
	{
		temp = token->next;
		if (token->token)
			free(token->token);
		free(token);
		token = temp;
	}
}

void	free_builtin(t_builtin *builtin)
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

void	all_free(t_minishell *minishell)
{
	free_cd_cmd_token(minishell->memorie_cd, minishell->token);
	free_builtin(minishell->builtin);
	if (minishell->line)
		free(minishell->line);
}
