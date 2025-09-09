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

static int	free_var_exist(char **name, char **result, int ex)
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

static int	remplace(char **str_new, int j, char *var, int len_name)
{
	char	*pre;
	char	*post;
	char	*new;
	int		len_post;

	len_post = len_name + 1 + j;
	pre = ft_substr(*str_new, 0, j);
	if (!pre)
		return (1);
	post = ft_substr(*str_new, len_post, ft_strlen(var) - len_post);
	if (!post)
	{
		free(pre);
		return (1);
	}
	new = ft_strjoin_var(3, pre, var, post);
	if (!new)
		return (1);
	free(pre);
	free(post);
	free(*str_new);
	*str_new = new;
	return (0);
}

int	var_exist(t_minishell *minishell, char **str_new, int j, char **name)
{
	char	*var;
	char	*result;

	result = NULL;
	if ((*str_new)[j + 1] == '?')
	{
		result = ft_itoa(minishell->data->exit_code);
		if (remplace(str_new, j, result, ft_strlen(result)))
			return (free_var_exist(name, &result, 1));
		return (free_var_exist(name, &result, 2));
	}
	var = search_env(minishell->data->env, *name);
	if (var)
	{
		if (remplace(str_new, j, var, ft_strlen(*name)))
			return (free_var_exist(name, NULL, 1));
		return (free_var_exist(name, NULL, 2));
	}
	if (remplace(str_new, j, NULL, ft_strlen(*name)))
		return (free_var_exist(name, NULL, 1));
	return (free_var_exist(name, NULL, 0));
}
