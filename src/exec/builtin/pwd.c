#include "minishell.h"

static char	*recup_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			return (env[i] + 4);
		i++;
	}
	return (NULL);
}

void	print_emplacement(t_shell *shell)
{
	char	*w_dir;

	w_dir = recup_pwd(shell->data->env);
	printf ("%s\n", w_dir);
	return ;
}
