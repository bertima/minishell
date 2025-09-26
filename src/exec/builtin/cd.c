#include "minishell.h"

int	strlen_av(char **av)
{
	int	i;

	i = 0;
	if (!av)
		return (0);
	while (av[i])
		i++;
	return (i);
}

char	*return_home(char *str)
{
	str = getenv("HOME");
	if (!str)
	{
		printf("bash: cd: HOME not set\n");
		return (NULL);
	}
	return (str);
}

void	dep_fd(char **av)
{
	char	*target_dir;

	target_dir = NULL;
	if (strlen_av(av) == 1 || av[1][0] == '~')
		target_dir = return_home(target_dir);
	else
	{
		target_dir = av[1];
		if (!target_dir)
		{
			printf("bash: cd: missing argument\n");
			return ;
		}
	}
	if (chdir(target_dir) != 0)
	{
		printf("bash: cd: %s: %s\n", target_dir, strerror(errno));
		return ;
	}
}
