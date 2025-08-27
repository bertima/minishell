/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:22:26 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/27 15:42:57 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_minishell *minishell, t_traitement *traitement)
{
	if (ft_strcmp(traitement->cmd_tab[0], "echo") == 0)
		echo(minishell);
	return (0);
}
