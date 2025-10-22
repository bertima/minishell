/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:36:53 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 13:36:54 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**update_pwd(char **env, char *newpwd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			ft_free(&env[i]);
			env[i] = ft_strjoin("PWD=", newpwd);
		}
		i++;
	}
	return (env);
}

char	**update_oldpwd(char **env, char *oldpwd, int oldpwd_found)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			ft_free(&env[i]);
			env[i] = ft_strjoin("OLDPWD=", oldpwd);
			oldpwd_found = 1;
		}
		i++;
	}
	return (env);
}

int	erreur_cd(t_shell *shell, char *prev_dir, char *target_dir)
{
	if (!prev_dir)
	{
		perror("getcwd");
		shell->data->exit_code = 1;
		return (1);
	}
	if (chdir(target_dir) != 0)
	{
		shell->data->exit_code = 1;
		perror("cd");
		free(prev_dir);
		return (1);
	}
	return (0);
}
