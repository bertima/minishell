/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:23:29 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:23:30 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update(t_shell *shell, char **av, int i)
{
	shell->data->exp = update_exp(shell->data->exp, av[i], NULL, 0);
	if (!shell->data->exp)
		return ;
	if (ft_strchr(av[i], '='))
	{
		shell->data->env = update_or_add_env(shell->data->env, av[i]);
		if (!shell->data->env)
			return ;
	}
}

int	check_char_export(char *var)
{
	int		i;

	i = 1;
	if (var[0] && (var[0] != '_' || ft_isalpha(var[0])))
	{
		while (var[i] && (var[i] != '='))
		{
			if ((var[i] != '_') && (ft_isalnum(var[i]) == 0))
				return (1);
			i++;
		}
	}
	return (0);
}
