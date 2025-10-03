#include "minishell.h"

void	modif_env(char **env, int i)
{
	free(env[i]);
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
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

int	check_option(char **av)
{
	if (av[1][0] == '-')
	{
		printf("les consigne ne demande pas de gere les option!\n");
		return (1);
	}
	return (0);
}

char	**unset(char **env, char **av)
{
	int	i;
	int	j;

	if (strlen_av(av) >= 2)
	{
		if (check_option(av) == 1)
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
	return (env);
}
