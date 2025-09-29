#include "minishell.h"

static int	manage_redir(t_redir *redir)
{
	size_t	fd;

	if (redir->type == MORE)
	{
		fd = open(*redir->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd < 0)
			perror(redir->file[0]);
		return (1);
	}
	else if (redir->type == REDIRECT_A)
	{
		fd = open(*redir->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
			perror(redir->file[0]);
		return (1);
	}
	else
	{
		if (access(redir->file[0], F_OK | R_OK))
		{
			perror(redir->file[0]);
			return (1);
		}
	}
	return (0);
}

static int	creat_file(t_redir *redir)
{
	t_redir	*temp_redir;

	temp_redir = redir;
	while (temp_redir)
	{
		if (temp_redir->type != HERE_DOC)
		{
			if (manage_redir(temp_redir))
				return (1);
		}
		else
		{
			if (manage_here_doc(temp_redir))
				return (1);
		}
		temp_redir = temp_redir->next;
	}
	return (0);
}

static int	manage_file_name(t_shell *shell, t_cmd *cmd, int i, int j)
{
	t_redir	*temp_red;

	temp_red = cmd->redir;
	while (temp_red)
	{
		if (temp_red->type != HERE_DOC)
		{
			temp_red->before_exp = ft_strdup(temp_red->file[0]);
			if (!temp_red->before_exp)
				return (1);
			if (loop_expand(shell, &temp_red->file, &i, &j))
				return (1);
			if (ft_len_array(temp_red->file) != 1)
				return (return_err_int(shell, "More than 1 arg\n"));
		}
		else
		{
			if (manage_here_doc(temp_red))
				return (1);
		}
		temp_red = temp_red->next;
	}
	return (0);
}

int	redirection_verif(t_shell *shell, t_cmd *cmd)
{
	if (manage_file_name(shell, cmd, 0, 0))
		return (1);
	if (creat_file(cmd->redir))
		return (1);
	return (0);
}
