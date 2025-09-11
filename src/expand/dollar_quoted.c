/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_exist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:20:22 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/08 14:54:26 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_env(char **env, char *name)
{
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(name, env[i], len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	free_dollar_exit(char **name, char **result, int ex)
{
	if (name && *name)
		free(*name);
	if (result && *result)
		free(*result);
	return (ex);
}

static int	dollar_in_env(t_shell *shell, char **str_new, int j, char **name)
{
	char	*var;

	var = search_env(shell->data->env, *name);
	if (var)
	{
		if (remplace(str_new, j, var, ft_strlen(*name)))
			return (free_dollar_exit(name, NULL, 1));
		return (free_dollar_exit(name, NULL, 2));
	}
	return (0);
}

static int	exit_value(t_shell *shell, char **str_new, int j, char **name)
{
	char	*result;

	if ((*str_new)[j + 1] == '?')
	{
		result = ft_itoa(shell->data->exit_code);
		if (remplace(str_new, j, result, ft_strlen(result)))
			return (free_dollar_exit(name, &result, 1));
		return (free_dollar_exit(name, &result, 2));
	}
	return (0);
}

int	dollar_quoted(t_shell *shell, char **str_new, int j, char **name)
{
	int		value;

	value = exit_value(shell, str_new, j, name);
	if (value > 0)
		return (value);
	value = dollar_in_env(shell, str_new, j, name);
	if (value > 0)
		return (value);
	if (remplace(str_new, j, NULL, ft_strlen(*name)))
		return (free_dollar_exit(name, NULL, 1));
	return (free_dollar_exit(name, NULL, 0));
}
