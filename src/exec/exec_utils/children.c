#include "minishell.h"

static void	parent(t_shell *shell, t_cmd *cmd, int pid)
{
	int	old_fd;

	old_fd = shell->children->fd_transi;
	if (cmd->next)
	{
		shell->children->fd_transi = shell->children->pipefd[0];
		close_fd(&shell->children->pipefd[1]);
	}
	else
	{
		close_fd(&shell->children->pipefd[0]);
		shell->children->fd_transi = -1;
	}
	close_fd(&cmd->fd_in);
	close_fd(&cmd->fd_out);
	close_fd(&old_fd);
	if (!cmd->next)
		shell->children->last_pid = pid;
}

static int	child_manage(t_shell *shell, t_cmd *cmd)
{
	if (shell->children->nbr_cmd > 1 && cmd->fd_in == -2)
	{
		if (dup2(shell->children->fd_transi, STDIN_FILENO) < 0)
			return (1);
	}
	if (cmd->next && cmd->fd_out == -2)
	{
		if (dup2(shell->children->pipefd[1], STDOUT_FILENO) < 0)
			return (perror(""), 1);
	}
	close_fd_cmd_shell(shell, cmd);
	if (exec_builtin(shell, &cmd))
		exit (shell->data->exit_code);
	exec_com(cmd->arg, shell->data->env);
	return (0);
}

void	creat_child(t_shell *shell, t_cmd *cmd, int pid)
{
	pid = fork();
	if (pid < 0)
		return (perror(""));
	else if (pid == 0)
	{
		if (redirect_command(shell, &cmd, 0))
			return ;
		close_fd(&shell->data->fd_stock_in);
		close_fd(&shell->data->fd_stock_out);
		child_manage(shell, cmd);
	}
	parent(shell, cmd, pid);
}

void	wait_parent(t_shell *shell)
{
	int		status;
	pid_t	pid;

	close_fd_cmd_shell(shell, NULL);
	while (shell->children->nbr_cmd > 0)
	{
		pid = wait(&status);
		if (pid == shell->children->last_pid)
		{
			if (WIFEXITED(status))
				shell->data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->data->exit_code = ft_sig(status);
		}
		shell->children->nbr_cmd--;
	}
}
