/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:52:14 by bertrmar          #+#    #+#             */
/*   Updated: 2025/06/14 09:14:00 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	compte(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*condition(void)
{
	char	*cond;

	cond = (char *)malloc(sizeof(char) * 2);
	if (!cond)
		return (NULL);
	cond[0] = '0';
	cond[1] = '\0';
	return (cond);
}

static long	min(char *str, long n)
{
	str[0] = '-';
	str[1] = '9';
	n = 223372036854775808 ;
	return (n);
}

char	*ft_ltoa(long n)
{
	long	i;
	char	*conv;

	if (n == 0)
		return (condition());
	i = compte(n);
	conv = (char *)malloc(sizeof(char) * (i + 1));
	if (!conv)
		return (NULL);
	if (n == LONG_MIN)
		n = min(conv, n);
	if (n < 0)
	{
		conv[0] = '-';
		n *= -1;
	}
	conv[i] = '\0';
	while (n > 0)
	{
		conv[i - 1] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (conv);
}
