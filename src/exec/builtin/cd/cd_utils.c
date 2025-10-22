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

char	*get_env_value(char **env, const char *key)
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

char	*stock_pwd(const char *s, int i)
{
	int		len;
	int		j;
	char	*str;

	len = i;
	while (s[len])
		len++;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (s[i])
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	**add_oldpwd(char **env, char *oldpwd)
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
		new_env[i] = env[i];
		i++;
	}
	new_env[i++] = ft_strjoin("OLDPWD=", oldpwd);
	new_env[i] = NULL;
	free(env);
	return (new_env);
}
