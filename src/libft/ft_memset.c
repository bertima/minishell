/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:11:30 by bertrmar          #+#    #+#             */
/*   Updated: 2025/04/21 09:15:57 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*ff;

	ff = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		ff[i] = (unsigned char)c;
		i++;
	}
	return (str);
}
