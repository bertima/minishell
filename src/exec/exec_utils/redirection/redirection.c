#include "minishell.h"

static int	here_doc_and_less(t_cmd *cmd, t_redir *redir)
{
	if (redir->type == LESS)
	{
		close_fd(&cmd->fd_in);
		if (access(redir->file[0], F_OK | R_OK) < 0)
			return (perror(redir->file[0]), 1);
		cmd->fd_in = open(redir->file[0], O_RDONLY);
		if (cmd->fd_in < 0)
			return (perror(""), 1);
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			return (1);
	}
	else if (redir->type == HERE_DOC)
	{
		close_fd(&cmd->fd_in);
		cmd->fd_in = open(redir->file_temp, O_RDONLY);
		if (cmd->fd_in < 0)
			return (perror(redir->file_temp), 1);
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			return (1);
	}
	return (0);
}

int	creat_dup(t_cmd *cmd, t_redir *redir)
{
	if (!redir)
		return (0);
	if (here_doc_and_less(cmd, redir))
		return (1);
	else if (redir->type == MORE)
	{
		close_fd(&cmd->fd_out);
		cmd->fd_out = open(*redir->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (cmd->fd_out < 0)
			return (perror(redir->file[0]), 1);
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			return (1);
	}
	else if (redir->type == REDIRECT_A)
	{
		close_fd(&cmd->fd_out);
		cmd->fd_out = open(*redir->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cmd->fd_out < 0)
			return (perror(redir->file[0]), 1);
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			return (1);
	}
	return (0);
}

static int	creat_dup_file(t_cmd *cmd, t_redir *redir)
{
	if (ft_len_array(redir->file) != 1)
		return (ft_putstr_fd("More than 1 arg fail creat file\n", 2), 1);
	if (creat_dup(cmd, redir))
		return (1);
	return (0);
}

static int	manage_expand(t_shell *shell, t_redir *redir, int i, int j)
{
	t_redir	*temp_red;

	temp_red = redir;
	temp_red->before_exp = ft_strdup(temp_red->file[0]);
	if (!temp_red->before_exp)
		return (1);
	if (expand_in_arg(shell, &temp_red->file, &i, &j))
		return (1);
	return (0);
}

int	redirect_cmd(t_shell *shell, t_cmd *cmd)
{
	t_redir	*temp_redir;

	temp_redir = cmd->redir;
	while (temp_redir)
	{
		manage_expand(shell, temp_redir, 0, 0);
		if (creat_dup_file(cmd, temp_redir))
			return (1);
		temp_redir = temp_redir->next;
	}
	return (0);
}
