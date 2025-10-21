#include "minishell.h"

char	**update_pwd_env(char **env, char *oldpwd, int i, char *newpwd)
{
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			ft_free(&env[i]);
			env[i] = ft_strjoin("OLDPWD=", oldpwd);
		}
		i++;
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		perror("minishell: getcwd");
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
			ft_free(&tmp);
		}
		else
			str = av;
	}
	return (str);
}

int	to_many_argument(char **av)
{
	if (strlen_av(av) > 2)
	{
		perror("bash: cd: too many arguments");
		return (1);
	}
	return (0);
}

char	**dep_fd(t_shell *shell, char **av, char **env)
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
	if (!prev_dir)
	{
		perror("getcwd");
		shell->data->exit_code = 1;
		return (env);
	}
	if (chdir(target_dir) != 0)
	{
		shell->data->exit_code = 1;
		perror("cd");
		free(prev_dir);
		return (env);
	}
	env = update_pwd_env(env, prev_dir, 0, NULL);
	if (prev_dir)
		free(prev_dir);
	shell->data->exit_code = 0;
	return (env);
}
