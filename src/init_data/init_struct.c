/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:26:27 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:26:29 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shell_levelup(t_shell *shell, char ***env, char *environ, int i)
{
	long	nbr_sh;
	char	*new_nbr_sh;

	nbr_sh = 0;
	if (ft_atol(&environ[6], &nbr_sh))
	{
		ft_putstr_fd("SHLVL not support more than max long\n", 2);
		nbr_sh = 0;
		shell->data->exit_code = 1;
	}
	if (nbr_sh < 0)
	{
		ft_putstr_fd("No negative support for SHLVL\n", 2);
		nbr_sh = 0;
		shell->data->exit_code = 1;
	}
	nbr_sh++;
	new_nbr_sh = ft_ltoa(nbr_sh);
	if (!new_nbr_sh)
		return (1);
	(*env)[i] = ft_strjoin("SHLVL=", new_nbr_sh);
	if (!(*env)[i])
		return (free(new_nbr_sh), 1);
	return (free(new_nbr_sh), 0);
}

static int	malloc_env(t_shell *shell, char ***env, char **environ, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (ft_strncmp(environ[i], "SHLVL=", 6) == 0)
		{
			if (shell_levelup(shell, env, environ[i], i))
				return (ft_free_split(*env), 1);
		}
		else
		{
			(*env)[i] = ft_strdup(environ[i]);
			if (!(*env)[i])
				return (ft_free_split(*env), 1);
		}
		i++;
	}
	(*env)[i] = NULL;
	return (0);
}

static int	copie_env(t_shell *shell, char ***env, char **environ)
{
	int	len;

	if (!environ || !environ[0])
		return (creat_env(env));
	len = ft_len_array(environ);
	(*env) = calloc(len + 1, sizeof(char *));
	if (!(*env))
		return (1);
	if (malloc_env(shell, env, environ, len))
		return (ft_free_split (*env), 1);
	return (0);
}

static int	init_export(char ***export, char **env)
{
	int	len;
	int	i;

	i = 0;
	len = ft_len_array(env);
	(*export) = calloc(len + 1, sizeof(char *));
	if (!(export))
		return (1);
	while (i < len)
	{
		(*export)[i] = ft_strdup(env[i]);
		if (!(*export)[i])
		{
			ft_free_split((*export));
			return (1);
		}
		i++;
	}
	(*export)[i] = NULL;
	return (0);
}

int	init_struct(t_shell *shell, char **environ)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->data = ft_calloc(1, sizeof(t_data));
	if (!shell->data)
		return (error_find_int(shell, MALLOC, 1, NULL));
	if (copie_env(shell, &shell->data->env, environ))
		return (error_find_int(shell, MALLOC, 1, NULL));
	if (init_export(&shell->data->exp, shell->data->env))
		return (error_find_int(shell, MALLOC, 1, NULL));
	shell->data->fd_stock_in = -1;
	shell->data->fd_stock_out = -1;
	return (0);
}
