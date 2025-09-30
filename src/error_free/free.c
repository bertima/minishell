#include "minishell.h"

static void	free_data_builtin(t_shell *shell)
{
	if (shell->data->env)
		ft_free_split(shell->data->env);
	shell->data->env = NULL;
	if (shell->data->line)
		free(shell->data->line);
	shell->data->line = NULL;
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
		redir->file = NULL;
		if (redir->before_exp)
			free(redir->before_exp);
		redir->before_exp = NULL;
		if (redir->before_exp)
			free(redir->before_exp);
		redir->before_exp = NULL;
		redir = temp;
	}
	redir = NULL;
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
		{
			free_redir(shell->cmd->redir);
			shell->cmd->redir = NULL;
			free(shell->cmd->redir);
			shell->cmd->redir = NULL;
		}
		free(shell->cmd);
		shell->cmd = NULL;
		shell->cmd = temp_c;
	}
}

void	free_command_redir_token(t_shell *shell)
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
	free_command_redir(shell);
}

void	all_free(t_shell *shell)
{
	if (!shell)
		return ;
	free_command_redir_token(shell);
	free_data_builtin(shell);
}
