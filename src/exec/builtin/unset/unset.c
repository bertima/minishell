#include "minishell.h"

void	unset_env(char **env, char **av)
{
	int	i;
	int	j;

	j = 1;
	while (av[j])
	{
		i = 0;
		while (env[i])
		{
			if (check_name_variable(env[i], av[j]) == 0)
			{
				modif_env(env, i);
				break ;
			}
			i++;
		}
		j++;
	}
}

void	unset_export(t_shell *shell, char **av)
{
	int	i;
	int	j;

	j = 1;
	while (av[j])
	{
		i = 0;
		while (shell->data->exp[i])
		{
			if (check_name_variable(shell->data->exp[i], av[j]) == 0)
			{
				modif_env(shell->data->exp, i);
				break ;
			}
			i++;
		}
		j++;
	}
}

char	**unset(t_shell *shell, char **env, char **av)
{
	if (ft_len_array(av) >= 2)
	{
		if (check_option(shell, av))
			return (env);
		unset_env(env, av);
		unset_export(shell, av);
	}
	shell->data->exit_code = 0;
	return (env);
}
