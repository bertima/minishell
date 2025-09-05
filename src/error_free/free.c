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

static void	free_data_builtin(t_minishell *minishell)
{
	if (minishell->data->env)
		ft_free_split(minishell->data->env);
	if (minishell->data->line)
		free(minishell->data->line);
	if (minishell->data->local_var)
		ft_free_split(minishell->data->local_var);
	if (minishell->builtin->doc_here_in)
		free(minishell->builtin->doc_here_in);
	if (minishell->builtin->doc_here_out)
		free(minishell->builtin->doc_here_out);
	if (minishell->builtin->pipe)
		free(minishell->builtin->pipe);
	if (minishell->builtin->echo)
		free(minishell->builtin->echo);
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

void	free_command_redir_token(t_minishell *minishell)
{
	t_token		*temp;
	t_command	*temp_c;

	while (minishell->token)
	{
		temp = minishell->token->next;
		if (minishell->token->sentence)
			free(minishell->token->sentence);
		free(minishell->token);
		minishell->token = temp;
	}
	while (minishell->command)
	{
		temp_c = minishell->command->next;
		if (minishell->command->arg)
			ft_free_split(minishell->command->arg);
		if (minishell->command->redir)
			free_redir(&minishell->command->redir);
		free(minishell->command);
		minishell->command = temp_c;
	}
}

void	all_free(t_minishell *minishell)
{
	if (!minishell)
		return ;
	free_command_redir_token(minishell);
	free_data_builtin(minishell);
}
