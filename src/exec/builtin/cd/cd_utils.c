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
		i++;
	}
	new_env[i++] = ft_strjoin("OLDPWD=", oldpwd);
	new_env[i] = NULL;
	free(env);
	return (new_env);
}

char	**add_oldpwd_export(t_shell *shell, char *oldpwd)
{
	int		i;
	char	**new_env;

	i = 0;
	while (shell->data->exp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (shell->data->exp);
	i = 0;
	while (shell->data->exp[i])
	{
		new_env[i] = ft_strdup(shell->data->exp[i]);
		i++;
	}
	new_env[i++] = ft_strjoin("OLDPWD=", oldpwd);
	new_env[i] = NULL;
	free(shell->data->exp);
	return (new_env);
}
