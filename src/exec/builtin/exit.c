#include "minishell.h"

int	is_numerique(char **av)
{
	int	i;

	i = 0;
	if (av[1][0] == '-')
		i++;
	while (av[1][i])
	{
		if (av[1][i] > '9' || av[1][i] < '0')
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument required\n", av[1]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_not_valid_av(t_shell *shell, char **av)
{
	if (av[1][0] == '-')
	{
		printf("les consigne ne demande pas de gere les option!\n");
		return (1);
	}
	if (av[1] && is_numerique(av) == 1)
	{
		all_free(shell);
		rl_clear_history();
		return (1);
	}
	if (strlen_av(av) > 1)
	{
		printf("exit\n");
		printf("bash: exit: too many arguments%s: \n", av[1]);
		return (1);
	}
	return (0);
}

void	end_prog(t_shell *shell, char **av)
{
	long long	ret;

	if (is_not_valid_av(shell, av) == 1)
		exit (2);
	if (strlen_av(av) == 1)
	{
		all_free(shell);
		rl_clear_history();
		printf("exit\n");
		exit(127);
	}
	if (strlen_av(av) > 1)
	{
		ret = 0;
		ft_atoll(av[1], &ret);
		if (ret > INT64_MAX || ret < INT64_MIN)
			exit(255);
		if (ret > 255 || ret < -255)
			ret = (ret % 256);
		all_free(shell);
		rl_clear_history();
		printf("exit\n");
		exit(ret);
	}
}
