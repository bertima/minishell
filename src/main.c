/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:00:10 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/25 17:01:08 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	programme(char *line, t_minishell *minishell)
{
	if (put_prompt(line, minishell))
		return ;
	if (parsing(minishell))
		return ;
	if (exec(minishell))
		return ;
}

int	main(int ac, char **av, char **environ)
{
	char			*line;
	t_minishell		minishell;

	if (ac != 1 || !av[0])
		return (return_err_int(NULL, "No argument for minishell !\n"));
	line = NULL;
	if (init_struct(&minishell))
		return (return_err_int(&minishell, NULL));
	if (cp_env(&minishell.data->env, environ))
		return (1);
	while (1)
	{
		programme(line, &minishell);
	}
	all_free(&minishell);
	rl_clear_history();
	return (0);
}
