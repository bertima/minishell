/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:35:57 by bertrmar          #+#    #+#             */
/*   Updated: 2025/09/05 15:43:04 by bertrmar         ###   ########.fr       */
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

static char	*search_name(char *str, int start)
{
	int		len;
	char	*name;

	len = 0;
	while (ft_isalnum(str[start + len]))
		len++;
	name = ft_substr(str, start, len);
	if (!name)
		return (NULL);
	return (name);
}

static int	loop(t_minishell *minishell, t_command *command, int i, int j)
{
	char		*name;
	char		*var;

	while (command->arg && command->arg[i] && command->arg[i][j])
	{
		if (command->arg[i][j] == '$')
		{
			name = search_name(command->arg[i], j + 1);
			if (name)
			{
				var = search_env(minishell->data->env, name);
				if (var)
				{
					if (var_exist(&command->arg[i], j, var, &name))
						return (1);
					continue ;
				}
				remplace(&command->arg[i], j, NULL, name);
				free(name);
			}
		}
		j++;
	}
	return (0);
}

int	expand(t_minishell *minishell, t_command *command, int i, int j)
{
	t_command	*temp;

	temp = command;
	while (temp)
	{
		i = 0;
		while (temp->arg && temp->arg[i])
		{
			j = 0;
			if (temp->arg[i][0] != '\'')
			{
				if (loop(minishell, temp, i, j))
					return (1);
			}
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
