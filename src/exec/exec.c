#include "minishell.h"

void	bultin(t_shell *shell)
{
	if (ft_strcmp(shell->cmd->arg[0], "echo") == 0)
		echo(shell->cmd->arg);
	if (ft_strcmp(shell->cmd->arg[0], "env") == 0)
		show_environ(shell->data->env);
	if (ft_strcmp(shell->cmd->arg[0], "exit") == 0)
		end_prog(shell, shell->cmd->arg);
	if (ft_strcmp(shell->cmd->arg[0], "pwd") == 0)
		print_emplacement();
	if (ft_strcmp(shell->cmd->arg[0], "cd") == 0)
		dep_fd(shell->cmd->arg);
	if (ft_strcmp(shell->cmd->arg[0], "export") == 0)
		export(shell->data->env, shell->cmd->arg);
	if (ft_strcmp(shell->cmd->arg[0], "unset") == 0)
		unset(shell->data->env, shell->cmd->arg);
}

int	exec(t_shell *shell)
{
	t_cmd	*cmd;

	if (expand(shell, shell->cmd, 0, 0))
		return (1);
	show_commands(shell->cmd, 0, 1);
	if (redirection(shell))
		return (1);
	cmd = shell->cmd;
	while (cmd)
	{
		if (cmd->arg)
		{
			bultin(shell);
		}
		cmd = cmd->next;
	}
	cmd = shell->cmd;
	return (0);
}
