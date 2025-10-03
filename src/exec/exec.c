#include "minishell.h"

static int	multi_command(t_shell *shell, t_cmd *cmd, int i)
{
	t_cmd	*temp_cmd;
	t_cmd	*last;

	temp_cmd = cmd;
	while (temp_cmd)
	{
		if (!temp_cmd->next)
			last = temp_cmd;
		redirect_command(shell, &temp_cmd, 0);
		/* voir comment implementer les pipe et les fork*/
		i++;
		temp_cmd = temp_cmd->next;
	}
	wait_parent(shell);
	if (redirect_command(shell, last, 1))
		return (1);
	return (0);
}

static int	one_cmd(t_shell *shell, t_cmd *cmd, int result)
{
	if (cmd->arg)
	{
		if (redirect_command(shell, &cmd, 0))
			return (1);
		result = exec_builtin(shell, &cmd);
		if (result == 0)
			execut_command(shell, cmd);
		if (redirect_command(shell, &cmd, 1))
			return (1);
	}
	return (0);
}

int	exec(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	shell->children->nbr_cmd = 0;
	while (cmd)
	{
		shell->children->nbr_cmd += 1;
		cmd = cmd->next;
	}
	cmd = shell->cmd;
	if (shell->children->nbr_cmd == 1)
		one_cmd(shell, cmd, 0);
	else if (shell->children->nbr_cmd > 1)
		multi_command(shell, cmd, 0);
	show_commands(shell->cmd, 0, 1);
	return (0);
}
