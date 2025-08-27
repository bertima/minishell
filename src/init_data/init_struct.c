/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 07:41:32 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/27 07:52:36 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_struct(t_minishell *minishell)
{
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->cmd_pipe = calloc(1, sizeof(t_cmd_pipe));
	if (!minishell->cmd_pipe)
		return (1);
	minishell->memorie_cd = calloc(1, sizeof(t_cd_memorie));
	if (!minishell->memorie_cd)
		return (1);
	minishell->traitement = calloc(1, sizeof(t_traitement));
	if (!minishell->traitement)
		return (1);
	minishell->builtin = ft_calloc(1, sizeof(t_builtin));
	if (!minishell->builtin)
		return (1);
	return (0);
}
