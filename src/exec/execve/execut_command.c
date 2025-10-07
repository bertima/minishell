#include "minishell.h"

static void	close_fd_cmd(t_shell *shell, t_cmd *cmd, int *temp_pipe)
{
	if (shell->children)
	{
		temp_pipe = shell->children->pipefd;
		if (temp_pipe && temp_pipe[0] && temp_pipe[0] >= 0)
		{
			close(temp_pipe[0]);
			temp_pipe[0] = -1;
		}
		if (temp_pipe && temp_pipe[0] && temp_pipe[1] && temp_pipe[1] >= 0)
		{
			close(temp_pipe[1]);
			temp_pipe[0] = -1;
		}
	}
	if (cmd->fd_in >= 0)
	{
		close(cmd->fd_in);
		cmd->fd_in = -2;
	}
	if (cmd->fd_out >= 0)
	{
		close(cmd->fd_out);
		cmd->fd_out = -2;
	}
}

int	execut_command(t_shell *shell, t_cmd *cmd)
{
	int	pid;
	int	status;

	(void)cmd;
	pid = fork();
	if (pid < 0)
		return (perror(""), 1);
	else if (pid == 0)
	{
		close_fd_cmd(shell, cmd, NULL);
		close(shell->data->fd_stock_in);
		close(shell->data->fd_stock_out);
		exec_com(cmd->arg, shell->data->env);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->data->exit_code = WEXITSTATUS(status);
	return (0);
}
