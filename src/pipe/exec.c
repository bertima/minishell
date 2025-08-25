/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:21:00 by bertrmar          #+#    #+#             */
/*   Updated: 2025/06/27 10:56:26 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			return (error_com(path));
		if (access(way, F_OK | X_OK) == 0)
		{
			ft_free_split(path);
			return (way);
		}
		free(way);
		i++;
	}
	return (error_com(path));
}

int	exec_com(char *av, char **environ)
{
	char	*path;
	char	**com;

	com = ft_split_chr(av, " \t\n\v\f\r", '\'');
	if (!com)
		exit (1);
	path = com_find(com[0], environ);
	if (!path)
	{
		path = ft_strjoin_var(3, "command not found: ", com[0], "\n");
		write (2, path, ft_strlen(path));
		free (path);
		ft_free_split(com);
		exit (127);
	}
	execve(path, com, environ);
	perror(av);
	ft_free_split(com);
	exit (126);
}
