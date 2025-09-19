#include "minishell.h"

void	show_environ(char **av)
{
	int	i;
	int	len;

	i = 0;
	len = ft_len_double_char(av);
	while (i < len)
	{
		printf("%s\n", av[i]);
		i++;
	}
}
