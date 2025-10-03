#include "minishell.h"

void	wait_parent(t_shell *shell)
{
	int		now;
	pid_t	pid;

	now = 0;
	while (shell->children->nbr_cmd > 0)
	{
		pid = wait(&now);
		if (pid == shell->children->last_pid)
			shell->children->status = now;
		shell->children->nbr_cmd--;
	}
}