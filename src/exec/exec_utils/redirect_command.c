#include "minishell.h"

static int	redir_cmd(t_cmd **cmd)
{
	if ((*cmd)->fd_in != -2)
	{
		if (dup2((*cmd)->fd_in, STDIN_FILENO) < 0)
			return (perror(""), 1);
	}
	if ((*cmd)->fd_out != -2)
	{
		if (dup2((*cmd)->fd_out, STDOUT_FILENO) < 0)
			return (perror(""), 1);
	}
	return (0);
}

int	redirect_command(t_shell *shell, t_cmd **cmd, int i)
{
	if (i == 0)
	{
		if (redir_cmd(cmd))
			return (1);
	}
	else if (i == 1)
	{
		if (dup2(shell->data->fd_stock_in, STDIN_FILENO) < 0)
			return (perror(""), 1);
		if (dup2(shell->data->fd_stock_out, STDOUT_FILENO) < 0)
			return (perror(""), 1);
	}
	return (0);
}
