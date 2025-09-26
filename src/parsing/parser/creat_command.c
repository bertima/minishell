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

int	creat_command(t_shell *shell)
{
	t_cmd		*cmd;
	t_token		*temp;

	temp = shell->token;
	cmd = NULL;
	while (temp)
	{
		if (compare(shell, &cmd, &temp))
			return (return_err_int(shell, "creat_command fail\n"));
	}
	return (0);
}
