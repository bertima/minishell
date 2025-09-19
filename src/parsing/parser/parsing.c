#include "minishell.h"

int	parsing(t_shell *shell)
{
	if (tokening(shell))
		return (return_err_int(shell, "Token\n"));
	lexeur(shell);
	if (creat_command(shell))
		return (return_err_int(shell, "Command\n"));
	return (0);
}
