/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:19:43 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:19:45 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	str_error(int e_code, char *str)
{
	if (e_code == QUOTE)
		ft_putstr_fd("Quote no close\n", 2);
	else if (e_code == ARG_MINISHELL)
		ft_putstr_fd("No argument for shell !\n", 2);
	else if (e_code == META)
	{
		ft_putstr_fd("bash: syntax error near unexpected token '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (e_code == MALLOC)
		ft_putstr_fd("Error: Malloc fail\n", 2);
	else if (e_code == AMBIGUOUS)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
}

char	*error_find_char(t_shell *shell, int e_code, int code_err, char *str)
{
	all_free(shell);
	str_error(e_code, str);
	shell->data->exit_code = code_err;
	return (NULL);
}

int	error_find_int(t_shell *shell, int e_code, int code_err, char *str)
{
	str_error(e_code, str);
	if (!shell)
		return (1);
	free_command_redir_token_children(shell);
	shell->data->exit_code = code_err;
	return (1);
}

void	warning_here_doc(t_shell *shell, char *av)
{
	char	*line;

	line = ft_itoa(shell->data->line_here_doc);
	ft_putstr_fd("\nbash: warning: here-document at line ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd("')\n", 2);
	free (line);
}
