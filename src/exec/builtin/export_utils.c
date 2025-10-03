#include "minishell.h"

void	show_ex(char **av)
{
	int	i;
	int	len;

	i = 0;
	len = ft_len_array(av);
	while (i < len)
	{
		printf("declare -x %s\n", av[i]);
		i++;
	}
}

void	tri_bubule(char **ex)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	len = ft_len_array(ex);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			if (ft_strcmp(ex[j], ex[j + 1]) > 0)
			{
				tmp = ex[j];
				ex[j] = ex[j + 1];
				ex[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
