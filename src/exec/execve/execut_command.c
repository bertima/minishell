#include "minishell.h"

int	execut_command(t_shell *shell, t_cmd *cmd)
{
	int	pid;

	(void)cmd;
	pid = fork();
	if (pid < 0)
		return (perror(""), 1);
	else if (pid == 0)
	{
		restore_default_signals();
		close(cmd->fd_in);
		close(cmd->fd_out);
		exec_com(cmd->arg, shell->data->env);
	}
	else
	{
		return (ft_sig(shell));
	}
	wait(NULL);
	return (0);
}
