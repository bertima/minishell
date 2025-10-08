#include "minishell.h"

int	execut_command(t_shell *shell, t_cmd *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (perror(""), 1);
	else if (pid == 0)
	{
		restore_default_signals();
		close_fd(&shell->data->fd_stock_in);
		close_fd(&shell->data->fd_stock_out);
		exec_com(cmd->arg, shell->data->env);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->data->exit_code = 128 + WTERMSIG(status);
	}
	return (0);
}

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
		return (shell->data->env = dep_fd(cmd->arg, shell->data->env), 1);
	if (ft_strcmp(shell->cmd->arg[0], "export") == 0)
		return (shell->data->env = export(shell->data->env, cmd->arg), 1);
	if (ft_strcmp(shell->cmd->arg[0], "unset") == 0)
		return (shell->data->env = unset(shell->data->env, shell->cmd->arg), 1);
	return (0);
}

int	exec_builtin(t_shell *shell, t_cmd **cmd)
{
	if (bultin(shell, (*cmd)))
		return (1);
	shell->data->exit_code = 0;
	return (0);
}
