/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:17:19 by bertrmar          #+#    #+#             */
/*   Updated: 2025/06/20 14:51:37 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_recup(t_cmd_pipe *data, int *pipefd, char **environ, char *av)
{
	if (data->stock_fd == -1)
	{
		data->stock_fd = open("/dev/null", O_RDONLY);
		if (data->stock_fd < 0)
			return ;
	}
	if (dup2(data->stock_fd, 0) < 0)
		exit(error_sys(data));
	if (dup2(pipefd[1], 1) < 0)
		exit(error_sys(data));
	close_fd(data);
	exec_com(av, environ);
	exit(error_sys(data));
}

void	child_transi(char **environ, char *av, t_cmd_pipe *data)
{
	pid_t	pid1;

	if (pipe(data->pipefd))
		exit(error_sys(data));
	pid1 = fork();
	if (pid1 < 0)
		exit (error_sys(data));
	else if (pid1 == 0)
		child_recup(data, data->pipefd, environ, av);
	close (data->pipefd[1]);
	close (data->stock_fd);
	data->stock_fd = data->pipefd[0];
	if (data->stock_fd < 0)
		error_sys(data);
}

static void	child_out(t_cmd_pipe *data, char **environ, char *av)
{
	if (data->stock_fd == -1)
	{
		data->stock_fd = open("/dev/null", O_RDONLY);
		if (data->stock_fd < 0)
			return ;
	}
	if (data->fd_w == -1)
	{
		data->fd_w = open("/dev/null", O_WRONLY);
		if (data->fd_w < 0)
			return ;
	}
	if (dup2(data->stock_fd, 0) < 0)
		exit (error_sys(data));
	if (dup2(data->fd_w, 1) < 0)
		exit (error_sys(data));
	close_fd(data);
	exec_com(av, environ);
	exit (127);
}

void	child_last(char **environ, char *av, t_cmd_pipe *data)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 < 0)
		exit (error_sys(data));
	else if (pid2 == 0)
		child_out(data, environ, av);
	data->pid = pid2;
}

void	wait_parent(t_cmd_pipe *data, int i)
{
	int		now;
	pid_t	pid;

	now = 0;
	while (i > 0)
	{
		pid = wait(&now);
		if (pid == data->pid)
			data->status = now;
		i--;
	}
}
