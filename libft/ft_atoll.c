/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:19:50 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/21 15:19:54 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	verif_neg(const char *str)
{
	int	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (i > 18)
			return (1);
		if (i == 18)
		{
			if (str[18] == '9')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	verif_pos(const char *str)
{
	int	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (i > 18)
			return (1);
		if (i == 18)
		{
			if (str[18] == '8' || str[18] == '9')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	verif_possible(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = -1;
		i++;
	}
	if (j < 0)
	{
		if (verif_neg(&str[i]))
			return (1);
	}
	if (j > 0)
	{
		if (verif_pos(&str[i]))
			return (1);
	}
	return (0);
}

static int	verif_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoll(char *str, long long *result)
{
	long long	i;
	long long	j;

	i = 0;
	j = 1;
	*result = 0;
	while (str[i] == '\n' || str[i] == '\f' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (verif_possible(&str[i]) || verif_num(&str[i]))
		return (1);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		*result = *result * 10 + (str[i] - '0');
		i++;
	}
	*result *= j;
	return (0);
}
