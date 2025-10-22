/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:22:19 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:22:21 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_home(char *str)
{
	str = getenv("HOME");
	if (!str)
	{
		printf("bash: cd: HOME not set\n");
		return (NULL);
	}
	return (str);
}

static char	*get_env_value(char **env, const char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*return_oldpwd(char **env)
{
	char	*str;

	str = get_env_value(env, "OLDPWD");
	if (!str)
	{
		printf("bash: cd: OLDPWD not set\n");
		return (NULL);
	}
	return (str);
}

char	**add_oldpwd_env(char **env, char *oldpwd)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (env);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (ft_free_split(new_env), NULL);
		i++;
	}
	new_env[i++] = ft_strjoin("OLDPWD=", oldpwd);
	if (!new_env)
		return (ft_free_split(new_env), NULL);
	new_env[i] = NULL;
	ft_free_split(env);
	return (new_env);
}

char	**add_oldpwd_export(t_shell *shell, char *oldpwd)
{
	int		i;
	char	**new_export;

	i = 0;
	while (shell->data->exp[i])
		i++;
	new_export = malloc(sizeof(char *) * (i + 2));
	if (!new_export)
		return (shell->data->exp);
	i = 0;
	while (shell->data->exp[i])
	{
		new_export[i] = ft_strdup(shell->data->exp[i]);
		if (!new_export[i])
			return (ft_free_split(new_export), NULL);
		i++;
	}
	new_export[i++] = ft_strjoin("OLDPWD=", oldpwd);
	if (!new_export[i - 1])
		return (ft_free_split(new_export), NULL);
	new_export[i] = NULL;
	ft_free_split(shell->data->exp);
	return (new_export);
}
