#include "minishell.h"

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
		close(cmd->fd_in);
		close(cmd->fd_out);
		exec_com(cmd->arg, shell->data->env);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->data->exit_code = WEXITSTATUS(status);
	return (0);
}
