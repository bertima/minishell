#include "minishell.h"

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

void	close_fd(int *fd)
{
	if (*fd >= 0)
		close(*fd);
	*fd = -1;
}

static int	redir_cmd(t_cmd **cmd)
{
	if ((*cmd)->fd_in >= 0)
	{
		if (dup2((*cmd)->fd_in, STDIN_FILENO) < 0)
			return (perror(""), 1);
		close_fd(&(*cmd)->fd_in);
	}
	if ((*cmd)->fd_out >= 0)
	{
		if (dup2((*cmd)->fd_out, STDOUT_FILENO) < 0)
			return (perror(""), 1);
		close_fd(&(*cmd)->fd_out);
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
