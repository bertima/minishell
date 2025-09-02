/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:40:34 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/28 16:14:48 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_minishell *minishell)
{
	if (tokening(minishell))
		return (return_err_int(minishell, NULL));
	return (0);
}
