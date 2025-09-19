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

void	free_expand(t_shell *shell)
{
	if (!shell->expand)
		return ;
	if (shell->expand->name_var && *shell->expand->name_var)
		free(shell->expand->name_var);
	if (shell->expand->var_val && *shell->expand->var_val)
		free(shell->expand->var_val);
	free(shell->expand);
}

void	free_command_redir_token(t_shell *shell)
{
	t_token		*temp;
	t_cmd		*temp_c;

	while (shell->token)
	{
		temp = shell->token->next;
		if (shell->token->sentence)
			free(shell->token->sentence);
		free(shell->token);
		shell->token = temp;
	}
	while (shell->cmd)
	{
		temp_c = shell->cmd->next;
		if (shell->cmd->arg)
			ft_free_split(shell->cmd->arg);
		if (shell->cmd->redir)
			free_redir(&shell->cmd->redir);
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
	free_expand(shell);
}

int	free_3var(char **first, char **sec, char **third, int ex)
{
	if (first && *first)
	{
		free(*first);
		*first = NULL;
	}
	if (sec && *sec)
	{
		free(*sec);
		*sec = NULL;
	}
	if (third && *third)
	{
		free(*third);
		*third = NULL;
	}
	return (ex);
}
