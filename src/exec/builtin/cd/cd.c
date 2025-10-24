/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:22:13 by bertrmar          #+#    #+#             */
/*   Updated: 2025/10/22 10:22:14 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**update_pwd_env(t_shell *shell, char **env, char *oldpwd)
{
	char	*newpwd;
	int		oldpwd_found;
	int		i;

	i = 0;
	oldpwd_found = 0;
	env = update_oldpwd(env, oldpwd, &oldpwd_found);
	if (!oldpwd_found)
	{
		env = add_oldpwd_env(env, oldpwd);
		shell->data->exp = add_oldpwd_export(shell, oldpwd);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		perror("minishell: getcwd");
	env = update_pwd(env, newpwd);
	ft_free(&newpwd);
	return (env);
}

char	*join_home(char *s1, char *s2, int i, int j)
{
	char	*result;
	int		len1;
	int		len2;		

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	j = 1;
	while (s2[j])
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}

char	*def_dir(char *av, char **env)
{
	char	*tmp;
	char	*str;

	if (!av || (av[0] == '~' && av[1] == '\0'))
		str = return_home(NULL);
	else if (av[0] == '-' && av[1] == '\0')
	{
		str = return_oldpwd(env);
		if (str)
			printf("%s\n", str);
	}
	else
	{
		if (av[0] == '~' && av[1] == '/')
		{
			tmp = return_home(NULL);
			str = join_home(tmp, av, 0, 1);
			if (!str)
				return (NULL);
			ft_free(&tmp);
		}
		else
			str = av;
	}
	return (str);
}

int	to_many_argument(char **av)
{
	if (ft_len_array(av) > 2)
	{
		perror("bash: cd: too many arguments");
		return (1);
	}
	return (0);
}

char	**move_fd(t_shell *shell, char **av, char **env)
{
	char	*target_dir;
	char	*prev_dir;

	target_dir = NULL;
	if (to_many_argument(av) == 1)
	{
		shell->data->exit_code = 1;
		return (env);
	}
	target_dir = def_dir(av[1], env);
	if (!target_dir)
		return (env);
	prev_dir = getcwd(NULL, 0);
	if (erreur_cd(shell, prev_dir, target_dir))
		return (env);
	env = update_pwd_env(shell, env, prev_dir);
	if (prev_dir)
		free(prev_dir);
	shell->data->exit_code = 0;
	return (env);
}
