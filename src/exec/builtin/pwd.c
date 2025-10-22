/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:23:49 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:23:50 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*recup_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			return (env[i] + 4);
		i++;
	}
	return (NULL);
}

void	print_emplacement(t_shell *shell)
{
	char	*w_dir;

	w_dir = recup_pwd(shell->data->env);
	printf ("%s\n", w_dir);
	return ;
}
