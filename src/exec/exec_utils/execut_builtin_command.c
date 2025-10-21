#include "minishell.h"

static void	parent(t_shell *shell, int status, int pid)
{
	signal(SIGINT, SIG_IGN);
	if (redirect_std(shell))
		return ;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->data->exit_code = ft_sig(status);
}

int	execut_command(t_shell *shell, t_cmd *cmd, int status)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (perror(""), 1);
	else if (pid == 0)
	{
		reset_child_signal();
		close_stock(shell);
		if (redirect_cmd(shell, cmd))
		{
			all_free(shell);
			exit(1);
		}
		close_fd_cmd_shell(shell, cmd);
		exec_com(shell, cmd->arg, shell->data->env);
	}
	parent(shell, status, pid);
	return (0);
}

int	bultin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strcmp(cmd->arg[0], "echo") == 0)
		return (echo(shell, cmd->arg), 1);
	if (ft_strcmp(cmd->arg[0], "env") == 0)
		return (show_environ(shell, shell->data->env), 1);
	if (ft_strcmp(cmd->arg[0], "exit") == 0)
		return (end_prog(shell, shell->cmd->arg), 1);
	if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		return (print_emplacement(shell), 1);
	if (ft_strcmp(cmd->arg[0], "cd") == 0)
		return (shell->data->env = dep_fd(shell, cmd->arg, shell->data->env), 1);
	if (ft_strcmp(cmd->arg[0], "export") == 0)
		return (export(shell, NULL, NULL), 1);
	if (ft_strcmp(cmd->arg[0], "unset") == 0)
		return (shell->data->env = unset(shell, shell->data->env, cmd->arg), 1);
	return (0);
}

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (shell->data->fd_stock_in < 0 || shell->data->fd_stock_out < 0)
		return (perror(""), 0);
	if (redirect_cmd(shell, cmd))
	{
		redirect_std(shell);
		shell->data->exit_code = 1;
		return (1);
	}
	bultin(shell, cmd);
	if (redirect_std(shell))
		return (1);
	return (0);
}

int	verif_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->arg[0], "echo") == 0
		|| ft_strcmp(cmd->arg[0], "env") == 0
		|| ft_strcmp(cmd->arg[0], "exit") == 0
		|| ft_strcmp(cmd->arg[0], "pwd") == 0
		|| ft_strcmp(cmd->arg[0], "cd") == 0
		|| ft_strcmp(cmd->arg[0], "export") == 0
		|| ft_strcmp(cmd->arg[0], "unset") == 0)
		return (1);
	return (0);
}
