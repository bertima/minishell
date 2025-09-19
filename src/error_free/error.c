#include "minishell.h"

char	*return_null(t_shell *shell)
{
	all_free(shell);
	return (NULL);
}

int	return_err_int(t_shell *shell, char *str)
{
	all_free(shell);
	ft_putstr_fd(str, 2);
	return (1);
}
