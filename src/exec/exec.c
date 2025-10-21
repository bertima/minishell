#include "minishell.h"

static int	multi_command(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*temp_cmd;
	int		pid;

	temp_cmd = cmd;
	shell->data->fd_stock_in = dup(STDIN_FILENO);
	shell->data->fd_stock_out = dup(STDOUT_FILENO);
	if (shell->data->fd_stock_in < 0 || shell->data->fd_stock_out < 0)
		return (perror(""), 1);
	while (temp_cmd)
	{
		pid = 0;
		shell->children->nbr_cmd++;
		if (temp_cmd->next)
		{
			if (pipe(shell->children->pipefd))
				return (1);
		}
		creat_child(shell, temp_cmd, pid);
		temp_cmd = temp_cmd->next;
	}
	wait_parent(shell);
	if (redirect_std(shell))
		return (1);
	return (0);
}

static int	one_cmd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->arg)
	{
		if (cmd->arg && cmd->arg[0] && cmd->arg[0][0] != '\0')
		{
			shell->data->fd_stock_in = dup(STDIN_FILENO);
			shell->data->fd_stock_out = dup(STDOUT_FILENO);
			if (shell->data->fd_stock_in < 0 || shell->data->fd_stock_out < 0)
				return (perror(""), 1);
			if (verif_builtin(cmd))
			{
				if (exec_builtin(shell, cmd))
					return (1);
			}
			else
				execut_command(shell, cmd, 0);
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
	return (0);
}
