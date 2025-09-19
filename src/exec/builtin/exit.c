#include "minishell.h"

void	end_prog(t_shell *shell)
{
	all_free(shell);
	rl_clear_history();
	printf("exit\n");
	exit(127);
}
