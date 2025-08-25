/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:02:09 by bertrmar          #+#    #+#             */
/*   Updated: 2025/06/27 11:29:28 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	one_cmd(char **environ, char **av, t_cmd_pipe *data)
{
	if (pipe(data->pipefd))
		exit (1);
	child_last(environ, av[2], data);
	close_fd(data);
	wait (NULL);
}

static void	loop_cmd(int ac, char **av, char **environ, t_cmd_pipe *data)
{
	int	i;

	i = 2;
	while (i < ac - 1)
	{
		if (i < ac - 2)
			child_transi(environ, av[i], data);
		else
			child_last(environ, av[i], data);
		i++;
	}
	close_fd(data);
	wait_parent(data, ac - 3);
}

void	order_management(int ac, char **av, char **environ, t_cmd_pipe *data)
{
	if (ac == 4)
		one_cmd(environ, av, data);
	else if (ac > 4)
		loop_cmd(ac, av, environ, data);
}
