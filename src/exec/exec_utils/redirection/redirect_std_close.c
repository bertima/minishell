#include "minishell.h"

void	close_fd(int *fd)
{
	if (*fd >= 0 && *fd != STDIN_FILENO && *fd != STDOUT_FILENO)
		close(*fd);
	*fd = -1;
}

void	close_stock(t_shell *shell)
{
	close_fd(&shell->data->fd_stock_in);
	close_fd(&shell->data->fd_stock_out);
}

void	close_fd_cmd_shell(t_shell *shell, t_cmd *cmd)
{
	if (!shell)
		return ;
	if (cmd)
	{
		close_fd(&cmd->fd_in);
		close_fd(&cmd->fd_out);
	}
	if (shell->children)
	{
		close_fd(&shell->children->fd_transi);
		close_fd(&shell->children->pipefd[0]);
		close_fd(&shell->children->pipefd[1]);
	}
}

int	redirect_std(t_shell *shell)
{
	if (dup2(shell->data->fd_stock_in, STDIN_FILENO) < 0)
	{
		shell->data->exit_code = 1;
		return (perror(""), 1);
	}
	close_fd(&shell->data->fd_stock_in);
	if (dup2(shell->data->fd_stock_out, STDOUT_FILENO) < 0)
	{
		shell->data->exit_code = 1;
		return (perror(""), 1);
	}
	close_fd(&shell->data->fd_stock_out);
	return (0);
}
