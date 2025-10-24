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

static int	error_numerique_required(t_shell *shell, char **av)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(av[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	all_free(shell);
	exit (2);
}

static int	is_numerique(char **av)
{
	int	i;

	i = 0;
	if (av[1][0] == '-')
		i++;
	while (av[1][i])
	{
		if (ft_isdigit(av[1][i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_not_valid_av(t_shell *shell, char **av, long long *ret)
{
	if (av && av[0] && ft_len_array(av) > 1)
	{
		if (ft_atoll(av[1], ret))
			error_numerique_required(shell, av);
		else if (is_numerique(av) == 1)
			error_numerique_required(shell, av);
		else if (ft_len_array(av) > 2)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			shell->data->exit_code = 1;
			return (1);
		}
	}
	return (0);
}

void	end_prog(t_shell *shell, char **av)
{
	long long	ret;
	int			exit_stock;

	ret = 0;
	if (is_not_valid_av(shell, av, &ret) == 1)
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
		if (ret > INT64_MAX || ret < INT64_MIN)
			exit(255);
		if (ret > 255 || ret < -255)
			ret = (ret % 256);
		all_free(shell);
		printf("exit\n");
		exit(ret);
	}
}
