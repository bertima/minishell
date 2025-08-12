/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:51:56 by bertrmar          #+#    #+#             */
/*   Updated: 2025/05/29 10:47:24 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	format_pointeur(va_list args, unsigned int count)
{
	void			*temp;
	unsigned long	res;
	unsigned long	i;

	temp = va_arg(args, void *);
	if (!temp)
	{
		write(1, "(nil)", 5);
		count = count + 5;
		return (count);
	}
	res = (unsigned long)temp;
	i = res;
	write(1, "0x", 2);
	count = count + 2;
	ft_putnbr_base_unsigned_long(i, 1, "0123456789abcdef");
	while (res != 0)
	{
		count++;
		res = res / 16;
	}
	return (count);
}

static unsigned int	no_char_spe(char c, unsigned int count)
{
	ft_putchar_fd(c, 1);
	count++;
	return (count);
}

static unsigned int	format_num(char c, va_list args, unsigned int count)
{
	if (c == 'd' || c == 'i')
		count = format_int(c, args, count);
	else if (c == 'x' || c == 'X' || c == 'u')
		count = format_unsigned_int(c, args, count);
	else
		count = format_pointeur(args, count);
	return (count);
}

static unsigned int	fonction_format(unsigned int count, va_list args, char c)
{
	if (c == 'c' || c == 's' || c == '%')
		count = format_char(c, args, count);
	else if (c == 'p' || c == 'd' || c == 'i'
		|| c == 'x' || c == 'X' || c == 'u')
		count = format_num(c, args, count);
	return (count);
}

int	ft_printf(char *format, ...)
{
	va_list			args;
	unsigned int	count;
	int				i;

	i = 0;
	count = 0;
	if (!format)
		return (0);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count = fonction_format(count, args, format[i]);
		}
		else
			count = no_char_spe(format[i], count);
		i++;
	}
	va_end(args);
	return (count);
}
