/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:20:19 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:20:21 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent(t_shell *shell, t_cmd *cmd, int pid)
{
	if (cmd->next)
	{
		close_fd(&shell->children->fd_transi);
		shell->children->fd_transi = shell->children->pipefd[0];
		close_fd(&shell->children->pipefd[1]);
	}
	else
		close_fd(&shell->children->pipefd[0]);
	if (!cmd->next)
		shell->children->last_pid = pid;
}

static int	child_manage(t_shell *shell, t_cmd *cmd)
{
	int	exit_code;

	if (shell->children->nbr_cmd > 1 && cmd->fd_in < 0)
	{
		if (dup2(shell->children->fd_transi, STDIN_FILENO) < 0)
			return (perror(""), 1);
		close_fd(&shell->children->fd_transi);
	}
	if (cmd->next && cmd->fd_out < 0)
	{
		if (dup2(shell->children->pipefd[1], STDOUT_FILENO) < 0)
			return (perror(""), 1);
		close_fd(&shell->children->pipefd[1]);
	}
	if (verif_builtin(cmd))
	{
		bultin(shell, cmd);
		exit_code = shell->data->exit_code;
		all_free(shell);
		exit (exit_code);
	}
	exec_com(shell, cmd->arg, shell->data->env);
	return (0);
}

void	creat_child(t_shell *shell, t_cmd *cmd, int pid)
{
	pid = fork();
	if (pid < 0)
		return (perror(""));
	else if (pid == 0)
	{
		reset_child_signal();
		if (redirect_cmd(shell, cmd))
		{
			all_free(shell);
			exit(1);
		}
		child_manage(shell, cmd);
	}
	parent(shell, cmd, pid);
}

void	wait_parent(t_shell *shell)
{
	int		status;
	pid_t	pid;

	while (shell->children->nbr_cmd > 0)
	{
		signal(SIGINT, SIG_IGN);
		pid = wait(&status);
		if (pid == shell->children->last_pid)
		{
			if (WIFEXITED(status))
				shell->data->exit_code = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				shell->data->exit_code = ft_sig(status);
		}
		shell->children->nbr_cmd--;
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
}
