/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:56:05 by bertrmar          #+#    #+#             */
/*   Updated: 2025/08/27 15:42:26 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*echo print ce qu'il y a derriere
-n evite le retour a la ligne*/

void	echo(t_minishell *minishell)
{
	int		i;
	char	*str;

	i = 0;
	while (minishell->traitement->cmd_tab[i])
	{
		if (ft_strcmp(minishell->traitement->cmd_tab[i], "echo") == 0)
			break ;
		i++;
	}
	str = minishell->traitement->cmd_tab[i + 1];
	if (!str)
		printf("\n");
	else if (ft_strcmp(str, "-n") == 0)
	{
		str = minishell->traitement->cmd_tab[i + 2];
		if (!str)
			return ;
		printf("%s", minishell->traitement->cmd_tab[i + 2]);
	}
	else if (ft_strcmp(str, "$?") == 0)
		printf("%d\n", minishell->cmd_pipe->exit_value);
	else
		printf("%s\n", str);
}
