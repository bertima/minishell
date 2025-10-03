#include "minishell.h"

static int	bultin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strcmp(cmd->arg[0], "echo") == 0)
		return (echo(cmd->arg), 1);
	if (ft_strcmp(cmd->arg[0], "env") == 0)
		return (show_environ(shell->data->env), 1);
	if (ft_strcmp(cmd->arg[0], "exit") == 0)
		return (end_prog(shell, shell->cmd->arg), 1);
	if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		return (print_emplacement(), 1);
	if (ft_strcmp(cmd->arg[0], "cd") == 0)
		return (dep_fd(shell->cmd->arg), 1);
	if (ft_strcmp(shell->cmd->arg[0], "export") == 0)
		shell->data->env = export(shell->data->env, shell->cmd->arg);
	if (ft_strcmp(shell->cmd->arg[0], "unset") == 0)
		shell->data->env = unset(shell->data->env, shell->cmd->arg);
	return (0);
}

int	exec_builtin(t_shell *shell, t_cmd **cmd)
{
	if (redirect_command(shell, cmd, 0))
		return (1);
	if (bultin(shell, (*cmd)))
	{
		if (redirect_command(shell, cmd, 1))
			return (1);
		return (2);
	}
	return (0);
}
