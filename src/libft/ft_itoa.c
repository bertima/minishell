/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:41:30 by bertrmar          #+#    #+#             */
/*   Updated: 2025/04/21 09:11:54 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	compte(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		i = 2;
		n = 147483648;
	}
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

static int	min(char *str, int n)
{
	str[0] = '-';
	str[1] = '2';
	n = 147483648;
	return (n);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*conv;

	if (n == 0)
		return (condition());
	i = compte(n);
	conv = (char *)malloc(sizeof(char) * i + 1);
	if (!conv)
		return (NULL);
	if (n == -2147483648)
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
