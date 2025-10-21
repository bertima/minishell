#include "minishell.h"

void	modif_env(char **env, int i)
{
	ft_free(&env[i]);
	while (env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
}

int	check_name_variable(char *env, char *av)
{
	int	j;

	j = 0;
	while (env[j] != '=')
	{
		if (av[j] != env[j])
			return (1);
		j++;
	}
	return (0);
}

int	check_option(t_shell *shell, char **av)
{
	if (av[1][0] == '-')
	{
		ft_putstr_fd("minishell : option not implement", 2);
		shell->data->exit_code = 2;
		return (1);
	}
	return (0);
}

char	**unset(t_shell *shell, char **env, char **av)
{
	int	i;
	int	j;

	if (ft_len_array(av) >= 2)
	{
		if (check_option(shell, av) == 1)
			return (env);
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
	shell->data->exit_code = 0;
	return (env);
}
