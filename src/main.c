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

int	main(int ac, char **environ)
{
	char			*line;
	t_minishell		minishell;

	if (ac != 1)
	{
		ft_putstr_fd("No argument required for minishell !\n", 2);
		return (1);
	}
	(void)environ;
	line = NULL;
	if (init_struct(&minishell))
		return (return_err_int(&minishell));
	while (1)
	{
		if (put_prompt(line, &minishell))
			break ;
		if (parsing(&minishell))
			break ;
	}
	rl_clear_history();
	return (0);
}
