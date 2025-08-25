/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:42:00 by bertrmar          #+#    #+#             */
/*   Updated: 2025/04/21 09:15:41 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*extend(unsigned char *s1, unsigned char *s2, void *dest, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return ((void *)dest);
	i = n - 1;
	while (i > 0)
	{
		s1[i] = s2[i];
		i--;
	}
	s1[i] = s2[i];
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tempdest;
	unsigned char	*tempsrc;

	if (!dest && !src)
		return (NULL);
	tempdest = (unsigned char *)dest;
	tempsrc = (unsigned char *)src;
	if (tempdest < tempsrc)
	{
		tempdest = (unsigned char *)ft_memcpy(dest, src, n);
	}
	else if (tempdest > tempsrc)
		extend(tempdest, tempsrc, dest, n);
	return (dest);
}
