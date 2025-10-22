/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:22:59 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:23:00 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numerique(char **av)
{
	int	i;

	i = 0;
	if (av[1][0] == '-')
		i++;
	while (av[1][i])
	{
		if (av[1][i] > '9' || av[1][i] < '0')
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(av[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_not_valid_av(t_shell *shell, char **av)
{
	if (ft_len_array(av) > 1)
	{
		if (av && av[0] && av[1] && av[1][0] == '-')
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("No option for exit\n", 2);
			shell->data->exit_code = 2;
			return (1);
		}
		else if (av && av[0] && av[1] && is_numerique(av) == 1)
		{
			shell->data->exit_code = 2;
			return (1);
		}
		else if (ft_len_array(av) > 2)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			shell->data->exit_code = 2;
			return (1);
		}
	}
	return (0);
}

void	end_prog(t_shell *shell, char **av)
{
	long long	ret;
	int			exit_stock;

	if (is_not_valid_av(shell, av) == 1)
		return ;
	if (ft_len_array(av) == 1)
	{
		exit_stock = shell->data->exit_code;
		all_free(shell);
		printf("exit\n");
		exit(exit_stock);
	}
	if (ft_len_array(av) > 1)
	{
		ret = 0;
		ft_atoll(av[1], &ret);
		if (ret > INT64_MAX || ret < INT64_MIN)
			exit(255);
		if (ret > 255 || ret < -255)
			ret = (ret % 256);
		all_free(shell);
		printf("exit\n");
		exit(ret);
	}
}
