/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:36:54 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/04 13:37:05 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	creat_env(void)
{
	return (0);
}

int	cp_env(char ***env, char **environ)
{
	int	i;
	int	len;

	i = 0;
	if (!environ)
		reutrn (creat_env());
	len = ft_len_double_char(environ);
	(*env) = calloc(len + 1, sizeof(char *));
	if (!(*env))
		return (1);
	while (i < len)
	{
		(*env)[i] = ft_strdup(environ[i]);
		if (!(*env)[i])
		{
			ft_free_split((*env));
			return (1);
		}
		i++;
	}
	(*env)[i] = NULL;
	return (0);
}

// A enlever au finale
/*void	show_environ(char **av)
{
	int i = 0;
	int len;

	len = ft_len_double_char(av);
	while (i < len)
	{
		printf("%s\n", av[i]);
		i++;
	}
}*/