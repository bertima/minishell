#include "minishell.h"

static int	compare(t_shell *shell, t_cmd **cmd, t_token **temp)
{
	if (!*cmd)
	{
		if (add_command(shell, cmd))
			return (1);
		return (0);
	}
	else if ((*temp)->type == PIPE)
	{
		if (add_command(shell, cmd))
			return (1);
	}
	else if ((*temp)->type != WORD)
	{
		if (manage_redirect_token(*cmd, temp))
			return (1);
	}
	else
	{
		if (add_arg(*cmd, *temp, 0))
			return (1);
	}
	*temp = (*temp)->next;
	return (0);
}

static void	clear_redir(t_redir *redir)
{
	t_redir	*temp_redir;

	temp_redir = redir;
	while (redir)
	{
		ft_free(&redir->before_exp);
		if (redir->file)
			ft_free_split(redir->file);
		redir->file = NULL;
		ft_free(&redir->file_temp);
		free(temp_redir);
		temp_redir = NULL;
		redir = redir->next;
	}
}

int	creat_command(t_shell *shell)
{
	t_cmd		*cmd;
	t_token		*temp;
	t_redir		*redir;

	temp = shell->token;
	cmd = NULL;
	while (temp)
	{
		if (compare(shell, &cmd, &temp))
		{
			redir = cmd->redir;
			clear_redir(redir);
			if (cmd && cmd->arg)
				ft_free_split(cmd->arg);
			return (error_find_int(shell, MALLOC, 1, NULL));
		}
	}
	return (0);
}
