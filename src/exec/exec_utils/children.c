#include "minishell.h"

static void	close_fd(t_shell *shell, t_cmd *cmd, int i)
{
	if (cmd)
	{
		if (cmd->fd_in >= 0)
			close (cmd->fd_in);
		cmd->fd_in = -1;
		if (cmd->fd_out >= 0)
			close (cmd->fd_out);
		cmd->fd_out = -1;
	}
	if (shell->children)
	{
		if (shell->children->fd_transi >= 0)
			close (shell->children->fd_transi);
		shell->children->fd_transi = -1;
		if (shell->children->pipefd[0] >= 0)
			close (shell->children->pipefd[0]);
		shell->children->pipefd[0] = -1;
		if (shell->children->pipefd[1] >= 0)
			close (shell->children->pipefd[1]);
		shell->children->pipefd[1] = -1;
	}
	if (i > 0)
	{
		close(shell->data->fd_stock_in);
		close (shell->data->fd_stock_out);
	}
}

static int	child_manage(t_shell *shell, t_cmd *cmd)
{
	if (shell->children->nbr_cmd > 1)
	{
		if (dup2(shell->children->fd_transi, STDIN_FILENO) < 0)
			return (1);
		if (cmd->fd_in >= 0)
		{
			close(cmd->fd_in);
			cmd->fd_in = -1;
		}
	}
	if (cmd->next)
	{
		if (dup2(shell->children->pipefd[1], STDOUT_FILENO) < 0)
			return (perror(""), 1);
		if (cmd->fd_out >= 0)
		{
			close(cmd->fd_out);
			cmd->fd_out = -1;
		}
	}
	if (exec_builtin(shell, &cmd))
		return (close_fd(shell, cmd, 1), shell->data->exit_code);
	if (execut_command(shell, cmd))
		return (1);
	return (0);
}

void	creat_child(t_shell *shell, t_cmd *cmd, int pid)
{
	if (redirect_command(shell, &cmd, 0))
		return ;
	pid = fork();
	if (pid < 0)
		return (perror(""));
	else if (pid == 0)
	{
		child_manage(shell, cmd);
		exit (shell->data->exit_code);
	}
}

int	parent(t_shell *shell, t_cmd *cmd, int pid)
{
	if (cmd->next)
	{
		close(shell->children->pipefd[1]);
		shell->children->pipefd[1] = -1;
	}
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	cmd->fd_in = -1;
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
	cmd->fd_out = -1;
	if (!cmd->next)
		shell->children->last_pid = pid;
	if (shell->children->fd_transi >= 0)
	{
		close (shell->children->fd_transi);
		shell->children->fd_transi = -1;
	}
	if (cmd->next)
		shell->children->fd_transi = shell->children->pipefd[0];
	return (0);
}

void	wait_parent(t_shell *shell)
{
	int		status;
	pid_t	pid;

	close_fd(shell, NULL, 0);
	while (shell->children->nbr_cmd > 0)
	{
		pid = wait(&status);
		if (pid == shell->children->last_pid)
		{
			if (WIFEXITED(status))
				shell->data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->data->exit_code = 128 + WTERMSIG(status);
		}
		shell->children->nbr_cmd--;
	}
}
