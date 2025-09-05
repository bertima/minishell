/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fonction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:03:31 by bertrmar          #+#    #+#             */
/*   Updated: 2025/05/01 13:15:17 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_base_unsigned(unsigned int nbr, int fd, char *base)
{
	char			c;
	unsigned int	len;

	len = 0;
	if (ft_check_base(base) == 0)
		return ;
	len = ft_strlen(base);
	if (nbr >= len)
		ft_putnbr_base_unsigned(nbr / len, 1, base);
	c = base[nbr % len];
	write (fd, &c, 1);
}

static unsigned int	format_u(unsigned int count, unsigned int temp)
{
	unsigned int	res;

	res = 0;
	res = temp;
	ft_putnbr_unsigned(temp, 1);
	if (res == 0)
		count++;
	while (res != 0)
	{
		count++;
		res = res / 10;
	}
	return (count);
}

unsigned int	format_int(char c, va_list args, unsigned int count)
{
	int	result;

	result = 0;
	if (c == 'd' || c == 'i')
	{
		result = va_arg(args, int);
		ft_putnbr_fd(result, 1);
		if (result == 0)
			count++;
		if (result < 0)
			count++;
		while (result != 0)
		{
			count++;
			result = result / 10;
		}
	}
	return (count);
}

unsigned int	format_unsigned_int(char c, va_list args, unsigned int count)
{
	unsigned int	temp;
	unsigned int	result;

	temp = 0;
	result = 0;
	if (c == 'X' || c == 'x' || c == 'u')
	{
		temp = va_arg(args, unsigned int);
		result = temp;
		if (c == 'X')
			ft_putnbr_base_unsigned(temp, 1, "0123456789ABCDEF");
		else if (c == 'x')
			ft_putnbr_base_unsigned(temp, 1, "0123456789abcdef");
		else
			count = format_u(count, temp);
		if (result == 0 && (c == 'x' || c == 'X'))
			count++;
		while (result != 0 && (c == 'x' || c == 'X'))
		{
			count++;
			result = result / 16;
		}
	}
	return (count);
}
