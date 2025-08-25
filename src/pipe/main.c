/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:28:38 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/11 15:30:28 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **environ)
{
	int		result;
	t_cmd_pipe	data;

	if (ac < 3)
	{
		ft_putstr_fd("To few arg !\n", 2);
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_cmd_pipe));
	result = verif_file(av, &data, ac);
	if (result == 2)
		here_doc(ac, av, environ, &data);
	else
		order_management(ac, av, environ, &data);
	if (WIFEXITED(data.status))
		return (WEXITSTATUS(data.status));
	return (0);
}