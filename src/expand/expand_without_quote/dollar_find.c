/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:03:24 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/11 15:25:55 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_dollar_exit(char **name, char **result, int ex)
{
	if (name && *name)
		free(*name);
	if (result && *result)
		free(*result);
	return (ex);
}

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

static int	join_word(char **str_expand, char **arg)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (arg && arg[i] && *arg[i])
	{
		temp = ft_strjoin(*str_expand, arg[i]);
		if (!temp)
		{
			if (str_expand)
				free(str_expand);
			return (1);
		}
		if (str_expand && *str_expand)
			free(*str_expand);
		*str_expand = temp;
		i++;
	}
	return (0);
}

static int	dollar_in_env(t_shell *shell, char **str_new, int j, char **name)
{
	char	*var;
	char	*str_expand;
	char	**arg;

	arg = NULL;
	str_expand = NULL;
	var = search_env(shell->data->env, *name);
	if (var)
	{
		if (word_splitting(&arg, var))
			return (1);
		if (join_word(&str_expand, arg))
			return (1);
		if (remplace(str_new, j, str_expand, ft_strlen(*name)))
			return (free_dollar_exit(name, NULL, 1));
		return (free_dollar_exit(name, NULL, 2));
	}
	if (remplace(str_new, j, NULL, ft_strlen(*name)))
		return (1);
	return (0);
}

static void	remove_arg(t_command *command, int i)
{
	int	index;

	index = i + 1;
	free(command->arg[i]);
	command->arg[i] = NULL;
	while (command->arg[i + index])
	{
		command->arg[i] = command->arg[index + i];
		index++;
	}
	command->arg[index + i] = NULL;
	return ;
}

int	dollar_find(t_shell *shell, t_command *command, int i, int *j)
{
	int		result;
	char	*name;
	char	*exit_code;

	if (command->arg[i][*j] == '$')
	{
		name = search_name(command->arg[i], *j + 1);
		if (command->arg[i][*j + 1] == '?')
		{
		exit_code = ft_itoa(shell->data->exit_code);
		if (remplace(&command->arg[i], *j, exit_code, ft_strlen(exit_code)))
			return (free_dollar_exit(&name, &exit_code, 1));
		return (free_dollar_exit(&name, &exit_code, 0));
		}
		if (name)
		{
			result = dollar_in_env(shell, &command->arg[i], *j, &name);
			if (result == 1)
				return (1);
		}
	}
	if (command->arg[i][0] == '\0')
		remove_arg(command, i);
	return (0);
}
