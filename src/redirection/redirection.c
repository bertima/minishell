#include "minishell.h"

static int	here_doc_and_less(t_cmd *temp_cmd, t_redir *redir)
{
	if (redir->type == LESS)
	{
		close_fd(&temp_cmd->fd_in);
		if (access(redir->file[0], F_OK | R_OK) < 0)
			return (perror(redir->file[0]), 1);
		temp_cmd->fd_in = open(redir->file[0], O_RDONLY);
		if (temp_cmd->fd_in < 0)
			return (perror(""), 1);
	}
	else if (redir->type == HERE_DOC)
	{
		close_fd(&temp_cmd->fd_in);
		temp_cmd->fd_in = open(redir->file_temp, O_RDONLY);
		if (temp_cmd->fd_in < 0)
			return (perror(redir->file_temp), 1);
	}
	return (0);
}

static int	manage_redir(t_cmd *temp_cmd, t_redir *redir)
{
	if (here_doc_and_less(temp_cmd, redir))
		return (1);
	else if (redir->type == MORE)
	{
		close_fd(&temp_cmd->fd_out);
		temp_cmd->fd_out = open(*redir->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (temp_cmd->fd_out < 0)
			return (perror(redir->file[0]), 1);
	}
	else if (redir->type == REDIRECT_A)
	{
		close_fd(&temp_cmd->fd_out);
		temp_cmd->fd_out = open(*redir->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (temp_cmd->fd_out < 0)
			return (perror(redir->file[0]), 1);
	}
	return (0);
}

static int	creat_file_manage_fd(t_cmd *temp_cmd, t_redir *redir)
{
	t_redir	*temp_redir;

	temp_redir = redir;
	while (temp_redir)
	{
		if (ft_len_array(temp_redir->file) != 1)
			return (ft_putstr_fd("More than 1 arg fail creat file\n", 2), 1);
		if (manage_redir(temp_cmd, temp_redir))
			return (1);
		temp_redir = temp_redir->next;
	}
	return (0);
}

static int	manage_expand_delimiter(t_shell *shell, t_cmd *cmd, int i, int j)
{
	t_redir	*temp_red;

	temp_red = cmd->redir;
	while (temp_red)
	{
		j = 0;
		if (temp_red->type != HERE_DOC)
		{
			temp_red->before_exp = ft_strdup(temp_red->file[0]);
			if (!temp_red->before_exp)
				return (1);
			if (expand_in_arg(shell, &temp_red->file, &i, &j))
				return (1);
		}
		else
		{
			if (manage_delimiter_hd(temp_red))
				return (1);
		}
		temp_red = temp_red->next;
	}
	return (0);
}

int	redirection_verif(t_shell *shell, t_cmd *temp_cmd)
{
	temp_cmd = shell->cmd;
	while (temp_cmd)
	{
		if (creat_here_doc(shell, temp_cmd, NULL, 0))
			return (1);
		temp_cmd = temp_cmd->next;
	}
	temp_cmd = shell->cmd;
	while (temp_cmd)
	{
		if (manage_expand_delimiter(shell, temp_cmd, 0, 0))
		{
			temp_cmd = temp_cmd->next;
			continue ;
		}
		if (creat_file_manage_fd(temp_cmd, temp_cmd->redir))
		{
			temp_cmd = temp_cmd->next;
			return (1);
		}
		temp_cmd = temp_cmd->next;
	}
	return (0);
}
