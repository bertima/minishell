#include "minishell.h"

static int	is_quoted(char *value)
{
	size_t	len;

	len = ft_strlen(value);
	if (len >= 2 && value[0] == '"' && value[len - 1] == '"')
		return (1);
	return (0);
}

static int	var_name_match(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = 0;
	len2 = 0;
	while (s1[len1] && s1[len1] != '=')
		len1++;
	while (s2[len2] && s2[len2] != '=')
		len2++;
	if (len1 != len2)
		return (0);
	i = 0;
	while (i < len1)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*quote_value(char *var)
{
	char	*eq_pos;
	char	*quoted;
	size_t	name_len;
	size_t	val_len;

	if (!var)
		return (NULL);
	eq_pos = ft_strchr(var, '=');
	if (!eq_pos)
		return (ft_strdup(var));
	name_len = eq_pos - var + 1;
	val_len = ft_strlen(eq_pos + 1);
	if (is_quoted(eq_pos + 1))
		return (ft_strdup(var));
	quoted = malloc(name_len + val_len + 3);
	if (!quoted)
		return (NULL);
	ft_memcpy(quoted, var, name_len);
	quoted[name_len] = '"';
	ft_memcpy(quoted + name_len + 1, eq_pos + 1, val_len);
	quoted[name_len + 1 + val_len] = '"';
	quoted[name_len + 1 + val_len + 1] = '\0';
	return (quoted);
}

int	var_exists(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (var_name_match(env[i], var))
			return (i);
		i++;
	}
	return (-1);
}

char	*remove_quotes_value(char *var)
{
	char	*eq_pos;
	char	*cleaned;
	size_t	name_len;
	size_t	val_len;

	if (!var)
		return (NULL);
	eq_pos = ft_strchr(var, '=');
	if (!eq_pos)
		return (ft_strdup(var));
	name_len = eq_pos - var + 1;
	val_len = ft_strlen(eq_pos + 1);
	if (!is_quoted(eq_pos + 1))
		return (ft_strdup(var));
	cleaned = malloc(name_len + val_len - 1);
	if (!cleaned)
		return (NULL);
	ft_memcpy(cleaned, var, name_len);
	ft_memcpy(cleaned + name_len, eq_pos + 2, val_len - 2);
	cleaned[name_len + val_len - 2] = '\0';
	return (cleaned);
}
