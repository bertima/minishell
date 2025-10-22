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
