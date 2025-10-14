#include "minishell.h"

int check_sign(char *av)
{
	int	i;

	i = 0;
	while(av[i])
	{
		if (av[i] == '=')
			return (1);
		i++;;
	}
	return (0);
}

void	show_environ(char **av)
{
	int	i;
	int	len;

	i = 0;
	len = ft_len_array(av);
	while (i < len)
	{
		printf("%s\n", av[i]);
		i++;
	}
}
