#include "minishell.h"

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
