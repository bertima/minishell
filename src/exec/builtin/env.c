#include "minishell.h"

void	show_environ(char **av)
{
	int	i;
	int	len;

	if (strlen_av(av) > 1)
	{
		printf("on  ne doit  pas gere les optiona ni les argumenta\n");
		return ;
	}
	i = 0;
	len = ft_len_array(av);
	while (i < len)
	{
		printf("%s\n", av[i]);
		i++;
	}
}
