/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:43:55 by bertrmar          #+#    #+#             */
/*   Updated: 2025/06/18 08:10:42 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_temp(char **temp, int fd)
{
	if (temp[fd])
	{
		free(temp[fd]);
		temp[fd] = NULL;
	}
	return (NULL);
}

static char	*verif_line(char **temp, int fd)
{
	char	*new;
	char	*rest;
	int		len_line;

	new = NULL;
	len_line = search_line(temp[fd]);
	if (len_line == 0)
		len_line = ft_strlen(temp[fd]);
	new = ft_substr(temp[fd], 0, len_line);
	if (!new)
		return (free_temp(temp, fd));
	rest = ft_substr(temp[fd], len_line, ft_strlen(temp[fd]) - len_line);
	if (!rest)
	{
		free(new);
		new = NULL;
		return (free_temp(temp, fd));
	}
	free(temp[fd]);
	temp[fd] = rest;
	return (new);
}

static void	win_5_line(char *buffer, ssize_t n, char **temp, int fd)
{
	buffer[n] = '\0';
	if (!temp[fd])
		temp[fd] = ft_strdup("");
}

static char	*alloc_line(char **temp, int fd)
{
	char	*join;
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	n;

	n = read(fd, buffer, BUFFER_SIZE);
	if (n < 0)
		return (free_temp(temp, fd));
	while (n > 0)
	{
		win_5_line(buffer, n, temp, fd);
		join = ft_strjoin(temp[fd], buffer);
		if (!join)
			return (free_temp(temp, fd));
		free(temp[fd]);
		temp[fd] = join;
		if (search_line(temp[fd]) > 0)
			break ;
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
			return (free_temp(temp, fd));
	}
	if (temp[fd] && *temp[fd])
		return (verif_line(temp, fd));
	return (free_temp(temp, fd));
}

char	*get_next_line(int fd)
{
	static char	*temp[1024];
	char		*str;
	int			i;

	i = 0;
	str = NULL;
	if (fd == -1)
	{
		while (i < 1024)
		{
			if (temp[i])
			{
				free(temp[i]);
				temp[i] = NULL;
			}
			i++;
		}
		return (NULL);
	}
	if (fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	str = alloc_line(temp, fd);
	return (str);
}
