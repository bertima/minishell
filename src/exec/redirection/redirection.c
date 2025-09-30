#include "minishell.h"

static int	manage_redir(t_redir *redir)
{
	size_t	fd;

	if (redir->type == LESS)
	{
		if (access(redir->file[0], F_OK | R_OK))
			return (perror(redir->file[0]), 1);
	}
	else if (redir->type == REDIRECT_A)
	{
		fd = open(*redir->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
			return (perror(redir->file[0]), 1);
	}
	else
	{
		fd = open(*redir->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd < 0)
			return (perror(redir->file[0]), 1);
	}
	return (0);
}

static int	creat_file_manage_fd(t_shell *shell, t_redir *redir)
{
	t_redir	*temp_redir;

	temp_redir = redir;
	while (temp_redir)
	{
		if (temp_redir->type != HERE_DOC)
		{
			if (ft_len_array(temp_redir->file) != 1)
				return (ft_putstr_fd("More than 1 arg\n", 2), 1);
			if (manage_redir(temp_redir))
				return (1);
		}
		else
		{
			if (manage_here_doc(shell, temp_redir))
				return (1);
		}
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

int	redirection_verif(t_shell *shell, t_cmd *cmd)
{
	if (manage_expand_delimiter(shell, cmd, 0, 0))
		return (1);
	if (creat_file_manage_fd(shell, cmd->redir))
		return (1);
	return (0);
}
