/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:40:34 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/27 15:46:22 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_minishell *minishell, t_traitement *traitement)
{
	if (search_quote(traitement))
		return (return_err_int(minishell));
	traitement->cmd_tab = ft_split(traitement->line, " \t\n\v\f\r");
	if (!traitement->cmd_tab)
		return (return_err_int(minishell));
	return (0);
}
