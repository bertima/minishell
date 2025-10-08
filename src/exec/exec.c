#include "minishell.h"

static int	multi_command(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*temp_cmd;
	int		pid;

	temp_cmd = cmd;
	while (temp_cmd)
	{
		pid = 0;
		shell->children->nbr_cmd++;
		if (temp_cmd->next)
		{
			if (pipe(shell->children->pipefd))
				return (1);
		}
		if (shell->children->nbr_cmd > 1)
		{
			if (dup2(shell->children->pipefd[0], STDIN_FILENO) < 0)
				return (1);
		}
		creat_child(shell, temp_cmd, pid);
		if (parent(shell, cmd, pid))
			return (1);
		temp_cmd = temp_cmd->next;
	}
	wait_parent(shell);
	return (0);
}

static int	one_cmd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->arg)
	{
		if (redirect_command(shell, &cmd, 0))
			return (1);
		if (cmd->arg && cmd->arg[0] && cmd->arg[0][0] != '\0')
		{
			if (!exec_builtin(shell, &cmd))
				execut_command(shell, cmd);
		}
	}
	return (0);
}

static int	creat_children_struct(t_shell *shell)
{
	t_children	*children;

	children = ft_calloc(1, sizeof(t_children));
	if (!children)
		return (1);
	shell->children = children;
	children->fd_transi = -1;
	children->pipefd[0] = -1;
	children->pipefd[1] = -1;
	return (0);
}

int	exec(t_shell *shell)
{
	t_cmd		*cmd;

	if (creat_children_struct(shell))
		return (1);
	cmd = shell->cmd;
	while (cmd)
	{
		shell->children->nbr_cmd += 1;
		cmd = cmd->next;
	}
	cmd = shell->cmd;
	if (shell->children->nbr_cmd == 1)
		one_cmd(shell, cmd);
	else if (shell->children->nbr_cmd > 1)
	{
		shell->children->nbr_cmd = 0;
		multi_command(shell, cmd);
	}
	if (redirect_command(shell, NULL, 1))
		return (1);
	return (0);
}
