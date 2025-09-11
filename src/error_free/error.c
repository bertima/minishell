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

char	*return_null(t_shell *shell)
{
	all_free(shell);
	return (NULL);
}

int	return_err_int(t_shell *shell, char *str)
{
	all_free(shell);
	ft_putstr_fd(str, 2);
	return (1);
}
