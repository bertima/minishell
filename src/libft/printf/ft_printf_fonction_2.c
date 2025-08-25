/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fonction_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:42:25 by bertrmar          #+#    #+#             */
/*   Updated: 2025/04/30 10:33:55 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	format_s(va_list args, unsigned int count)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
	{
		write (1, "(null)", 6);
		count = count + 6;
		return (count);
	}
	count = count + ft_strlen(str);
	ft_putstr_fd(str, 1);
	return (count);
}

unsigned int	format_char(char c, va_list args, unsigned int count)
{
	if (c == 'c')
	{
		c = (char)va_arg(args, int);
		ft_putchar_fd((int)c, 1);
		count++;
	}
	else if (c == 's')
		count = format_s(args, count);
	else if (c == '%')
	{
		c = '%';
		ft_putchar_fd(c, 1);
		count++;
	}
	return (count);
}

void	ft_putnbr_base_unsigned_long(unsigned long nbr, int fd, char *base)
{
	char			c;
	unsigned long	len;

	len = ft_strlen(base);
	if (ft_check_base(base) == 0)
		return ;
	if (nbr >= len)
		ft_putnbr_base_unsigned_long(nbr / len, 1, base);
	c = base[nbr % len];
	write (fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2", 2);
		n = 147483648;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write (fd, &c, 1);
}
