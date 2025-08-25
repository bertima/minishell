/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:53:08 by bertrmar          #+#    #+#             */
/*   Updated: 2025/04/21 11:07:11 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_sep(char c, const char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (0);
		i++;
	}
	return (1);
}

static int	number_del(const char *str, const char *sep)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	while (ft_sep(str[i], sep) == 0 && str[i])
	{
		i++;
		number++;
	}
	if (!(i == number && str[i] == '\0'))
	{
		i = ft_len(str) - 1;
		while (ft_sep(str[i], sep) == 0)
		{
			i--;
			number++;
		}
	}
	return (number);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		alloc_num;
	int		i;
	char	*trim;
	int		j;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	alloc_num = ft_len(s1) - number_del(s1, set);
	trim = (char *)malloc(sizeof(char) * alloc_num + 1);
	if (!trim)
		return (NULL);
	while (ft_sep(s1[i], set) == 0 && s1[i])
		i++;
	while (j < alloc_num)
	{
		trim[j] = s1[i];
		i++;
		j++;
	}
	trim[j] = '\0';
	return (trim);
}
