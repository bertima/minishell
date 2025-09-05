/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:50:56 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/25 16:51:13 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_str1_empty(char *s2, char *join)
{
	int	i;

	i = 0;
	join = malloc(sizeof(char) * (ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (s2 && s2[i])
	{
		join[i] = s2[i];
		i++;
	}
	join[i] = '\0';
	return (join);
}

static char	*ft_str2_empty(char *s1, char *join)
{
	int	i;

	i = 0;
	join = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!join)
		return (NULL);
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	join[i] = '\0';
	return (join);
}

static void	copie_join(char *s1, char *s2, char *join)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*join;

	join = NULL;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_str1_empty(s2, join));
	if (!s2)
		return (ft_str2_empty(s1, join));
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	copie_join(s1, s2, join);
	return (join);
}
