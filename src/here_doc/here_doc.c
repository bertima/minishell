/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:35:10 by bertrmar          #+#    #+#             */
/*   Updated: 2025/06/30 11:13:15 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_first(pid_t pid, char **av, t_cmd_pipe *data)
{
	if (pid < 0)
		exit(error_sys(data));
	else if (pid == 0)
	{
		if (dup2(data->fd_r, 1) < 0)
			exit (error_sys(data));
		if (recup_in(av))
			exit (1);
		close_fd(data);
		exit (0);
	}
	close (data->fd_r);
	data->fd_r = -1;
}

static void	child_second(pid_t pid2, char **env, char **av, t_cmd_pipe *data)
{
	if (pid2 < 0)
		exit (error_sys(data));
	else if (pid2 == 0)
	{
		if (dup2(data->stock_fd, 0) < 0)
			exit (error_sys(data));
		if (dup2(data->pipefd[1], 1) < 0)
			exit (error_sys(data));
		close_fd(data);
		exec_com(av[3], env);
		exit (error_sys(data));
	}
}

static void	child_third(pid_t pid3, char **environ, char **av, t_cmd_pipe *data)
{
	if (pid3 < 0)
		exit (error_sys(data));
	else if (pid3 == 0)
	{
		if (dup2(data->pipefd[0], 0) < 0)
			exit (error_sys(data));
		if (dup2(data->fd_w, 1) < 0)
			exit (error_sys(data));
		close_fd(data);
		exec_com(av[4], environ);
		exit (error_sys(data));
	}
	data->pid = pid3;
	close_fd(data);
}

static void	child(char **environ, char **av, t_cmd_pipe *data, char *file_temp)
{
	pid_t	pid;
	pid_t	pid2;
	pid_t	pid3;

	pid = fork();
	child_first(pid, av, data);
	data->stock_fd = open(file_temp, O_RDONLY);
	if (data->stock_fd < 0)
		exit (error_sys(data));
	wait (NULL);
	if (pipe(data->pipefd))
		exit (error_sys(data));
	pid2 = fork();
	child_second(pid2, environ, av, data);
	pid3 = fork();
	child_third(pid3, environ, av, data);
	if (unlink(file_temp) < 0)
		exit (error_sys(data));
}

void	here_doc(int ac, char **av, char **environ, t_cmd_pipe *data)
{
	char	*file_temp;

	file_temp = "pipex_recup_temp_here_doc_delete_after_use";
	unlink(file_temp);
	data->fd_r = open(file_temp, O_WRONLY | O_CREAT, 0600);
	if (data->fd_r < 0)
		exit (error_sys(data));
	data->fd_w = open(av[ac - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (data->fd_w < 0)
		exit (error_sys(data));
	child(environ, av, data, file_temp);
	wait_parent(data, data->pid);
}
