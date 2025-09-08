/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:34:04 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/08 10:34:15 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_environ(char **av)
{
	int	i;
	int	len;

	i = 0;
	len = ft_len_double_char(av);
	while (i < len)
	{
		printf("%s\n", av[i]);
		i++;
	}
}
