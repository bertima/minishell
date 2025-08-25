/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:17:08 by bertrmar          #+#    #+#             */
/*   Updated: 2025/06/19 14:38:08 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_cmd_pipe *data)
{
	if (data->pipefd[0] >= 0)
		close (data->pipefd[0]);
	if (data->pipefd[1] >= 0)
		close (data->pipefd[1]);
	if (data->fd_r >= 0)
		close (data->fd_r);
	if (data->fd_w >= 0)
		close (data->fd_w);
	if (data->stock_fd >= 0)
		close (data->stock_fd);
}

int	error_sys(t_cmd_pipe *data)
{
	close_fd(data);
	perror("");
	return (1);
}

int	error_arg(void)
{
	ft_putstr_fd("arg no valid\n", 2);
	return (1);
}

char	*error_com(char **path)
{
	ft_free_split(path);
	return (NULL);
}
