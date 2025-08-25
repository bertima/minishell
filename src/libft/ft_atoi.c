/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:09:03 by bertrmar          #+#    #+#             */
/*   Updated: 2025/04/21 09:09:44 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	verif_neg(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] == '0')
		j++;
	while (str[j + i] >= '0' && str[j + i] <= '9')
	{
		if (i > 18)
			return (0);
		if (i == 18)
		{
			if (str[18] == '9')
				return (0);
		}
		i++;
	}
	return (1);
}

static int	verif_pos(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
		j++;
	while (str[j + i] >= '0' && str[j + i] <= '9')
	{
		if (i > 18)
			return (0);
		if (i == 18)
		{
			if (str[18] == '8' || str[18] == '9')
				return (0);
		}
		i++;
	}
	return (1);
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
		if (verif_neg(&str[i]) != 1)
			return (0);
	}
	if (j > 0)
	{
		if (verif_pos(&str[i]) != 1)
			return (-1);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	result;

	i = 0;
	j = 1;
	result = 0;
	while (str[i] == '\n' || str[i] == '\f' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (verif_possible(&str[i]) != 1)
		return (verif_possible(&str[i]));
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	result *= j;
	return (result);
}
