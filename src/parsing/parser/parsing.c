/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:40:34 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/04 11:39:14 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_shell *shell)
{
	if (tokening(shell))
		return (return_err_int(shell, "Token\n"));
	lexeur(shell);
	if (creat_command(shell))
		return (return_err_int(shell, "Command\n"));
	return (0);
}
