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

int	init_struct(t_minishell *minishell, char **environ)
{
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->data = ft_calloc(1, sizeof(t_data));
	if (!minishell->data)
		return (1);
	if (cp_env(&minishell->data->env, environ))
		return (1);
	return (0);
}
