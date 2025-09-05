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

static char	*search_local_env(t_local_var *local, char **env, char *nameiable)
{
	int			i;
	int			len;
	int			len_name;
	t_local_var	*temp;

	i = 0;
	len = ft_strlen(nameiable);
	temp = local;
	while (temp)
	{
		len_name = ft_strlen(temp->name);
		if (ft_strncmp(nameiable, temp->name, len) == 0 && len == len_name)
			return (temp->value);
		temp = temp->next;
	}
	while (env[i])
	{
		if (ft_strncmp(nameiable, env[i], len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*search_name(char *str, int j)
{
	int		len;
	int		start;
	char	*name;

	start = j;
	len = 0;
	while (ft_isalnum(str[start + len]))
		len++;
	name = ft_substr(str, j, len + j);
	if (name < 0)
		return (NULL);
	return (name);
}

static int	remplace(char **rem, int j, char *var)
{
	char	*pre;
	char	*post;
	char	**new;
	int		len_rem;

	len_rem = ft_strlen(rem);
	pre = ft_substr(*rem, 0, j);
	if (!pre)
		return (1);
	post = ft_substr(*rem, j + 1, len_rem - (len_rem - (j + 1)));
	if (!post)
	{
		free(pre);
		return (1);
	}
	new = ft_strjoin_var(3, pre, var, post);
	if (!rem)
		return (1);
	free(pre);
	free(post);
	free(rem);
	rem = new;
}

static int	loop(t_minishell *minishell, t_command *command, int i, int j)
{
	char		*name;
	char		*var;
	t_local_var	*temp;

	temp = minishell->data->local_var;
	while (command->arg && command->arg[i][j])
	{
		if (command->arg[i][j] == '$')
		{
			name = search_name(command->arg[i], j + 1);
			if (name && *name)
			{
				var = search_local_env(temp, minishell->data->env, var);
				if (var)
				{
					if (remplace(&command->arg[i], j, name))
						return (1);
					continue ;
				}
			}
		}
		j++;
	}
	return (0);
}

int	expand(t_minishell *minishell, t_command *command, int i, int j)
{
	char	*name;
	char	*var;

	while (command)
	{
		while (command->arg && command->arg[i])
		{
			j = 0;
			if (loop(minishell, command, i, j))
				return (1);
			i++;
		}
		command = command->next;
	}
	return (0);
}
