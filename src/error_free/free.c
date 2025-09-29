#include "minishell.h"

static void	free_data_builtin(t_shell *shell)
{
	if (shell->data->env)
		ft_free_split(shell->data->env);
	if (shell->data->line)
		free(shell->data->line);
	return ;
}

static void	free_redir(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		temp = redir->next;
		if (redir->file)
			ft_free_split(redir->file);
		if (redir->before_exp)
			free(redir->before_exp);
		redir = temp;
	}
}

void	free_command_redir_token(t_shell *shell)
{
	t_token		*temp_token;
	t_cmd		*temp_c;

	while (shell->token)
	{
		temp_token = shell->token->next;
		if (shell->token->sentence)
			free(shell->token->sentence);
		free(shell->token);
		shell->token = temp_token;
	}
	while (shell->cmd)
	{
		temp_c = shell->cmd->next;
		if (shell->cmd->arg)
			ft_free_split(shell->cmd->arg);
		if (shell->cmd->redir)
		{
			free_redir(shell->cmd->redir);
			free(shell->cmd->redir);
		}
		free(shell->cmd);
		shell->cmd = temp_c;
	}
}

void	all_free(t_shell *shell)
{
	if (!shell)
		return ;
	free_command_redir_token(shell);
	free_data_builtin(shell);
}
