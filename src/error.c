/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 07:58:02 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/27 08:57:22 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stop_free(t_minishell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->memorie_cd)
		free (minishell->memorie_cd);
	if (minishell->cmd_pipe)
		free (minishell->cmd_pipe);
	if (minishell->traitement)
		free (minishell->traitement);
}

char	*return_null(t_minishell *minishell)
{
	stop_free(minishell);
	return (NULL);
}

int	return_err_int(t_minishell *minishell)
{
	stop_free(minishell);
	return (1);
}
