/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:26:46 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:26:47 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

static void	programme(char *line, t_shell *shell)
{
	if (put_prompt(line, shell))
		return ;
	if (g_exit_code == 130)
	{
		shell->data->exit_code = 130;
		g_exit_code = 0;
	}
	if (parsing(shell))
		return ;
	if (expand(shell, shell->cmd, 0, 0))
		return ;
	if (here_doc(shell, NULL))
		return ;
	exec(shell);
}

int	main(int ac, char **av, char **environ)
{
	char		*line;
	t_shell		shell;

	if (ac != 1 || !av[0])
		return (error_find_int(NULL, ARG_MINISHELL, 1, NULL));
	line = NULL;
	if (init_struct(&shell, environ))
		return (1);
	while (1)
	{
		setup_parent_signal();
		programme(line, &shell);
		free_command_redir_token_children(&shell);
	}
	all_free(&shell);
	return (0);
}
