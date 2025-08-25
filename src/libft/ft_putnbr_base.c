/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:19:31 by bertrmar          #+#    #+#             */
/*   Updated: 2025/04/25 11:16:35 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(int nbr, char *base)
{
	int		len;
	int		result;
	char	c;
	int		temp;

	len = ft_strlen(base);
	temp = nbr;
	if (ft_check_base(base) == 1)
	{
		if (temp < 0)
		{
			write (1, "-", 1);
			temp *= -1;
		}
		if (temp > len)
		{
			ft_putnbr_base(temp / len, base);
		}
		result = temp % len;
		c = base[result];
		write (1, &c, 1);
	}
}
