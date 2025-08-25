/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:04 by bertrmar          #+#    #+#             */
/*   Updated: 2025/06/17 14:44:43 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_ok(char str, char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (str == c[i])
			return (1);
		i++;
	}
	return (0);
}

static int	counter(const char *str, char *c)
{
	int	i;
	int	count;
	int	wall;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	wall = 0;
	while (str[i])
	{
		if (char_ok(str[i], c) == 1 && wall == 1)
			wall = 0;
		if (char_ok(str[i], c) == 0 && wall == 0)
		{
			wall = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static void	free_split(char **str, int j)
{
	int	i;

	i = j - 1;
	while (i >= 0)
	{
		free(str[i]);
		str[i] = (NULL);
		i--;
	}
	free(str);
	str = NULL;
}

static char	**alloc_str(char **new, char const *s, char *c)
{
	int	i;
	int	j;
	int	h;

	i = 0;
	j = i;
	h = 0;
	while (s[i])
	{
		while (char_ok(s[i], c) == 1)
			i++;
		j = i;
		if (s[i] == '\0')
			break ;
		while (char_ok(s[i], c) == 0 && s[i])
			i++;
		new[h] = ft_substr(s, j, i - j);
		if (!new[h])
		{
			free_split(new, h);
			return (NULL);
		}
		h++;
	}
	return (new);
}

char	**ft_split(char const *s, char *c)
{
	char	**new;

	if (!s)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (counter(s, c) + 1));
	if (!new)
		return (NULL);
	new = alloc_str(new, s, c);
	if (new)
		new[counter(s, c)] = NULL;
	return (new);
}
