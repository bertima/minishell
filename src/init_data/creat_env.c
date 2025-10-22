/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:26:19 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:26:21 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	creat_env(char ***env)
{
	char	*temp;

	*env = calloc(4, sizeof(char *));
	if (!*env)
		return (1);
	temp = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:");
	if (!temp)
	{
		free(*env);
		return (1);
	}
	(*env)[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	(*env)[1] = ft_strdup("SHLVL=1");
	(*env)[2] = ft_strjoin(temp, "/usr/sbin:/usr/bin:/sbin:/bin");
	(*env)[3] = NULL;
	if (!(*env)[0] || !(*env)[1] || !(*env)[2])
	{
		ft_free_split(*env);
		return (1);
	}
	return (0);
}
