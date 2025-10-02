#include "minishell.h"

static char	*search_path(char **environ)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

static char	**split_path(char **environ)
{
	char	*pathstr;
	char	**path;

	pathstr = search_path(environ);
	if (!pathstr)
		return (NULL);
	path = ft_split(pathstr, ":");
	if (!path)
		return (NULL);
	return (path);
}

static char	*com_find(char *av, char **environ)
{
	char	**path;
	int		i;
	char	*way;

	i = 0;
	path = split_path(environ);
	if (!path || !av)
		return (NULL);
	while (path[i])
	{
		way = ft_strjoin_var(3, path[i], "/", av);
		if (!way)
			return (ft_free_split(path), NULL);
		if (access(way, F_OK | X_OK) == 0)
		{
			ft_free_split(path);
			return (way);
		}
		free(way);
		i++;
	}
	return (ft_free_split(path), NULL);
}

int	exec_com(t_shell *shell, char **av, char **environ)
{
	char	*path;

	path = com_find(av[0], environ);
	if (!path)
	{
		path = ft_strjoin_var(3, "command not found: ", av[0], "\n");
		write (2, path, ft_strlen(path));
		free (path);
		shell->data->exit_code = 127;
		exit (127);
	}
	execve(path, av, environ);
	perror(av[0]);
	shell->data->exit_code = 126;
	exit (126);
}
