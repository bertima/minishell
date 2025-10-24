/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:22:49 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:22:51 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verif_environ(t_shell *shell, t_cmd *cmd)
{
	int	len;

	len = ft_len_array(cmd->arg);
	if (len > 1)
	{
		ft_putstr_fd("No arg support for env\n", 2);
		shell->data->exit_code = 2;
		return (1);
	}
	return (0);
}

void	show_environ(t_shell *shell, t_cmd *cmd, char **av)
{
	int	i;
	int	len;

	i = 0;
	if (verif_environ(shell, cmd))
		return ;
	len = ft_len_array(av);
	while (i < len)
	{
		printf("%s\n", av[i]);
		i++;
	}
	shell->data->exit_code = 0;
}
