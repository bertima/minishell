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

int	parsing(t_minishell *minishell)
{
	if (tokening(minishell))
		return (return_err_int(minishell, "Token\n"));
	lexeur(minishell);
	creat_command(minishell);
//		return (return_err_int(minishell, "creat_command fail\n"));
	free_command_token(minishell->command, minishell->token);
	return (0);
}
