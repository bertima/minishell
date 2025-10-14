#include "minishell.h"

void	close_stock(t_shell *shell)
{
	if (shell->data->fd_stock_in >= 0)
		close_fd(&shell->data->fd_stock_in);
	if (shell->data->fd_stock_out >= 0)
		close_fd(&shell->data->fd_stock_out);
}

void	close_fd_cmd_shell(t_shell *shell, t_cmd *cmd)
{
	if (!shell)
		return ;
	if (cmd)
	{
		if (cmd->fd_in >= 0)
			close_fd(&cmd->fd_in);
		if (cmd->fd_out >= 0)
			close_fd(&cmd->fd_out);
	}
	if (shell->children)
	{
		if (shell->children->fd_transi >= 0)
			close_fd(&shell->children->fd_transi);
		if (shell->children->pipefd[0] >= 0)
			close_fd(&shell->children->pipefd[0]);
		if (shell->children->pipefd[1] >= 0)
			close_fd(&shell->children->pipefd[1]);
	}
}

void	close_fd(int *fd)
{
	if (*fd >= 0 && *fd != STDIN_FILENO && *fd != STDOUT_FILENO)
		close(*fd);
	*fd = -1;
}

int	redirect_std(t_shell *shell)
{
	if (dup2(shell->data->fd_stock_in, STDIN_FILENO) < 0)
		return (1);
	close_fd(&shell->data->fd_stock_in);
	if (dup2(shell->data->fd_stock_out, STDOUT_FILENO) < 0)
		return (1);
	close_fd(&shell->data->fd_stock_out);
	return (0);
}
