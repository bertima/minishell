#include "minishell.h"

void	show_environ(t_shell *shell, char **av)
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
	shell->data->exit_code = 0;
}
