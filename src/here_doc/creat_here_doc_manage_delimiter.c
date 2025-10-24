/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_here_doc_manage_delimiter.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:33:19 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/24 10:33:20 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_delimiter_hd(t_redir *redir)
{
	int		i;
	char	**arg;

	if (!redir)
		return (0);
	i = 0;
	arg = redir->file;
	while (arg[0] && arg[0][i])
	{
		if (arg[0][i] == '\'' || arg[0][i] == '\"')
		{
			redir->hd_expand = 1;
			break ;
		}
		i++;
	}
	if (loop_remove_quote(&redir->file, 0, 0))
		return (1);
	return (0);
}

static int	expand_hd(t_shell *shell, char **temp, int *j, char **str)
{
	int	result;
	int	i;

	i = 0;
	while ((*temp)[*j])
	{
		if ((*temp)[*j] == '$')
		{
			result = exit_code_expand(shell, temp, &i, j);
			if (result == 1)
				return (1);
			else if (result == 2)
				continue ;
			if ((*temp)[*j + 1] && ft_valid_expand((*temp)[*j + 1]))
			{
				if (search_expand(shell, &temp, &i, j))
					return (1);
				continue ;
			}
		}
		(*j)++;
	}
	*str = temp[0];
	return (0);
}

static int	read_input(t_shell *shell, t_redir *redir, char *str, int fd_temp)
{
	int		j;
	char	*temp[2];

	j = 0;
	temp[0] = str;
	temp[1] = NULL;
	if (!redir->hd_expand)
	{
		if (expand_hd(shell, temp, &j, &str))
			return (1);
	}
	ft_putstr_fd(str, fd_temp);
	ft_free(&str);
	write(1, "> ", 2);
	return (0);
}

int	recup_in(t_shell *shell, t_redir *redir, char *av, int fd_temp)
{
	char	*str;
	char	*word_stop;

	word_stop = ft_strjoin(av, "\n");
	if (!word_stop)
		return (error_find_int(shell, MALLOC, 1, NULL));
	signal(SIGINT, gst_handler_here_doc);
	write(1, "> ", 2);
	str = get_next_line(STDIN_FILENO);
	while (str)
	{
		if (ft_strcmp(str, word_stop) == 0)
		{
			get_next_line(-1);
			ft_free(&str);
			break ;
		}
		if (read_input(shell, redir, str, fd_temp))
			return (error_find_int(shell, MALLOC, 1, NULL));
		str = get_next_line(STDIN_FILENO);
	}
	ft_free(&word_stop);
	return (0);
}

int	creat_here_doc(t_shell *shell, t_cmd *temp_cmd, char *file_temp, int fd)
{
	t_redir	*temp_redir;

	temp_redir = temp_cmd->redir;
	while (temp_redir)
	{
		if (temp_redir->type == HERE_DOC)
		{
			if (generator_of_file_name(&file_temp, NULL, NULL))
				return (error_find_int(shell, MALLOC, 1, NULL));
			fd = open(file_temp, O_WRONLY | O_CREAT, 0600);
			if (fd < 0)
				return (perror(""), unlink(file_temp), 1);
			if (recup_in(shell, temp_redir, temp_redir->file[0], fd))
				return (close(fd), unlink(file_temp), 1);
			close(fd);
			temp_redir->file_temp = ft_strdup(file_temp);
			if (!temp_redir->file_temp)
				return (error_find_int(shell, MALLOC, 1, NULL));
			ft_free(&file_temp);
		}
		temp_redir = temp_redir->next;
	}
	return (0);
}
