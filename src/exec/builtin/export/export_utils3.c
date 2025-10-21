#include "minishell.h"

void	update(t_shell *shell, char **av, int i)
{
	shell->data->exp = update_exp(shell->data->exp, av[i], NULL, 0);
	if (!shell->data->exp)
		return ;
	if (ft_strchr(av[i], '='))
	{
		shell->data->env = update_or_add_env(shell->data->env, av[i]);
		if (!shell->data->env)
			return ;
	}
}
