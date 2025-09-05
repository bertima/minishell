/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:18:33 by bertrmar          #+#    #+#             */
/*   Updated: 2025/04/22 10:14:24 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*str;
	size_t	tot;

	tot = size * number;
	if (size != 0 && tot / size != number)
		return (NULL);
	str = (unsigned char *)malloc(size * number);
	if (!str)
		return (NULL);
	ft_bzero(str, (number * size));
	return ((void *)str);
}
