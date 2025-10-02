#include "minishell.h"

static int	multi_command(t_shell *shell, t_cmd *cmd, int result)
{
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(shell->data->pipefd))
				return (perror(""), 1);
			if (i >= 1)
			{
				if (dup2(shell->data->pipefd[0], STDIN_FILENO))
					return (1);
				close (cmd->fd_in);
			}
		}
		result = exec_builtin(shell, &cmd);
		if (result == 1)
			return (1);
		else if (result == 2)
			continue ;
		if (execut_command(shell, cmd))
			return (1);
		if (redirect_command(shell, &cmd, 1))
			return (1);
	}
	return (0);
}

static int	one_cmd(t_shell *shell, t_cmd *cmd, int result)
{
	if (cmd->arg)
	{
		result = exec_builtin(shell, &cmd);
		if (result == 1)
			return (1);
		else if (result == 2)
			return (0);
		execut_command(shell, cmd);
		if (redirect_command(shell, &cmd, 1))
			return (1);
	}
	return (0);
}

int	exec(t_shell *shell, int i)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	cmd = shell->cmd;
	if (i == 1)
	{
		one_cmd(shell, cmd, 0);
		return (0);
	}
	else if (i > 1)
		multi_command(shell, cmd, 0);
	show_commands(shell->cmd, 0, 1);
	return (0);
}
