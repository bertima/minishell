#include "minishell.h"

static void	free_data(t_shell *shell)
{
	if (shell->data->env)
		ft_free_split(shell->data->env);
	shell->data->env = NULL;
	if (shell->data->line)
		free(shell->data->line);
	shell->data->line = NULL;
	if (shell->data->fd_stock_in >= 0)
		close (shell->data->fd_stock_in);
	if (shell->data->fd_stock_out >= 0)
		close (shell->data->fd_stock_out);
	return ;
}

static void	free_redir(t_cmd *cmd)
{
	t_redir	*temp;

	temp = cmd->redir;
	while (temp)
	{
		if (temp->before_exp)
			free(temp->before_exp);
		temp->before_exp = NULL;
		if (temp->file)
			ft_free_split(temp->file);
		temp->file = NULL;
		if (temp->file_temp)
		{
			unlink(temp->file_temp);
			free(temp->file_temp);
		}
		temp->file_temp = NULL;
		temp = temp->next;
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

	while (shell->token)
	{
		temp_token = shell->token->next;
		if (shell->token->sentence)
			free(shell->token->sentence);
		free(shell->token);
		shell->token = temp_token;
	}
	if (shell->children)
		free(shell->children);
	shell->children = NULL;
	free_command_redir(shell);
}

void	all_free(t_shell *shell)
{
	if (!shell)
		return ;
	free_command_redir_token_children(shell);
	free_data(shell);
	rl_clear_history();
}
