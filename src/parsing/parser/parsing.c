/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:27:57 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:27:58 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_shell *shell)
{
	if (tokening(shell))
		return (1);
	if (lexeur(shell))
		return (1);
	if (creat_command(shell))
		return (1);
	return (0);
}
