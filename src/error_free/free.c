/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:19:49 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:19:54 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_data(t_shell *shell)
{
	if (shell->data->env)
		ft_free_split(shell->data->env);
	shell->data->env = NULL;
	if (shell->data->exp)
		ft_free_split(shell->data->exp);
	shell->data->exp = NULL;
	ft_free(&shell->data->line);
	ft_free(&shell->data->w_dir_prompt);
	close_fd(&shell->data->fd_stock_in);
	close_fd(&shell->data->fd_stock_out);
	free(shell->data);
	return ;
}

static void	free_redir(t_cmd *cmd)
{
	t_redir	*temp;
	t_redir	*next;

	temp = cmd->redir;
	while (temp)
	{
		next = temp->next;
		ft_free(&temp->before_exp);
		if (temp->file)
			ft_free_split(temp->file);
		temp->file = NULL;
		if (temp->file_temp)
		{
			unlink(temp->file_temp);
			ft_free(&temp->file_temp);
		}
		free(temp);
		temp = next;
	}
	temp = NULL;
}

static void	free_command_redir(t_shell *shell)
{
	t_cmd	*temp_c;

	while (shell->cmd)
	{
		temp_c = shell->cmd->next;
		if (shell->cmd->arg)
			ft_free_split(shell->cmd->arg);
		shell->cmd->arg = NULL;
		if (shell->cmd->redir)
			free_redir(shell->cmd);
		free(shell->cmd);
		shell->cmd = NULL;
		shell->cmd = temp_c;
	}
}

void	free_command_redir_token_children(t_shell *shell)
{
	t_token		*temp_token;

	free_command_redir(shell);
	while (shell->token)
	{
		temp_token = shell->token->next;
		ft_free(&shell->token->sentence);
		free(shell->token);
		shell->token = temp_token;
	}
	if (shell->children)
	{
		close_fd(&shell->children->pipefd[0]);
		close_fd(&shell->children->pipefd[1]);
		close_fd(&shell->children->fd_transi);
		free(shell->children);
		shell->children = NULL;
	}
	ft_free(&shell->data->line);
}

void	all_free(t_shell *shell)
{
	if (!shell)
		return ;
	free_command_redir_token_children(shell);
	free_data(shell);
	rl_clear_history();
}
