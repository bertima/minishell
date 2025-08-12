/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:50:56 by bertrmar          #+#    #+#             */
/*   Updated: 2025/04/21 09:19:13 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static char	*ft_cat(const char *s1, const char *s2, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_len(s1);
	len2 = ft_len(s2);
	join = (char *)malloc(sizeof(char) * (len1 + len2) + 1);
	if (!join)
		return (NULL);
	join = ft_cat(s1, s2, join);
	return (join);
}
