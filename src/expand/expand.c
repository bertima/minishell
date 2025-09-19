#include "minishell.h"

static int	loop_expand(t_shell *shell, t_cmd *cmd, int i, int j)
{
	int			result;

	while (cmd->arg && cmd->arg[i] && cmd->arg[i][j])
	{
		result = quote_process(shell, cmd, &i, &j);
		if (result == 1)
			return (1);
		if (result == 2)
			continue ;
		result = expand_without_quote(shell, cmd, &i, &j);
		if (result == 1)
			return (1);
		if (result == 2)
			continue ;
		j++;
	}
	return (0);
}

int	expand(t_shell *shell, t_cmd *cmd, int i, int j)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		i = 0;
		shell->expand->cmd = temp;
		while (temp->arg && temp->arg[i])
		{
			j = 0;
			shell->expand->current_str = temp->arg[i];
			if (loop_expand(shell, temp, i, j))
				return (1);
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
