#include "minishell.h"

int	exec(t_shell *shell)
{
	t_cmd	*cmd;

	if (expand(shell, shell->cmd, 0, 0))
		return (1);
	show_commands(shell->cmd, 0, 1);
	cmd = shell->cmd;
	while (cmd)
	{
		if (cmd->arg)
		{
			if (ft_strcmp(shell->cmd->arg[0], "echo") == 0)
				echo(shell->cmd->arg);
			if (ft_strcmp(shell->cmd->arg[0], "env") == 0)
				show_environ(shell->data->env);
			if (ft_strcmp(shell->cmd->arg[0], "exit") == 0)
				end_prog(shell);
			if (ft_strcmp(shell->cmd->arg[0], "pwd") == 0)
				print_emplacement();
			if (ft_strcmp(shell->cmd->arg[0], "cd") == 0)
				dep_fd(shell->cmd->arg);
		}
		cmd = cmd->next;
	}
	cmd = shell->cmd;
	return (0);
}
