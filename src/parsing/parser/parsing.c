#include "minishell.h"

int	parsing(t_shell *shell)
{
	if (tokening(shell))
		return (1);
	if (lexeur(shell))
		return (1);
	if (creat_command(shell))
		return (1);
	return (0);
}
