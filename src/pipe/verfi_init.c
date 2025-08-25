/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verfi_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:37:33 by bertrmar          #+#    #+#             */
/*   Updated: 2025/06/26 14:04:33 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_fd(t_cmd_pipe *data, int ac)
{
	data->pipefd[0] = -1;
	data->pipefd[1] = -1;
	data->fd_r = -1;
	data->fd_w = -1;
	data->stock_fd = -1;
	data->ac = ac;
}

static void	no_cmd(char **av, t_cmd_pipe *data)
{
	if (access(av[1], F_OK | R_OK))
		exit (error_sys(data));
	data->fd_r = open (av[1], O_RDONLY);
	if (data->fd_r < 0 && data->stop == 0)
		exit(error_sys(data));
	data->fd_w = open(av[data->ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->fd_w < 0)
	{
		perror(av[data->ac - 1]);
		exit (1);
	}
}

static int	multi_arg(char **av, t_cmd_pipe *data)
{
	if (ft_strcmp(av[1], "here_doc") == 0)
		return (2);
	if (access(av[1], F_OK | R_OK))
	{
		perror(av[1]);
		data->stop = 1;
	}
	data->fd_r = open (av[1], O_RDONLY);
	if (data->fd_r < 0 && data->stop == 0)
		perror(av[1]);
	data->fd_w = open(av[data->ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->fd_w < 0)
		perror(av[data->ac - 1]);
	data->stock_fd = data->fd_r;
	return (0);
}

int	verif_file(char **av, t_cmd_pipe *data, int ac)
{
	init_fd(data, ac);
	if (ac == 3)
		no_cmd(av, data);
	else
		multi_arg(av, data);
	return (0);
}
