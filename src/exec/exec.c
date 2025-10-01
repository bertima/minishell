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
	if (ft_strcmp(cmd->arg[0], "export") == 0)
		return (export(shell->data->env, shell->cmd->arg), 1);
	if (ft_strcmp(cmd->arg[0], "unset") == 0)
		return (unset(shell->data->env, shell->cmd->arg), 1);
	return (0);
}

int	exec(t_shell *shell)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = shell->cmd;
	while (cmd)
	{
		if (cmd->arg)
		{
			if (cmd->arg[0])
			{
				if (bultin(shell, cmd))
				{
					cmd = cmd->next;
    	        	continue ;
				}
        		child(shell, cmd);
			}
		}
		i++;
		cmd = cmd->next;
	}
	show_commands(shell->cmd, 0, 1);
	return (0);
}
