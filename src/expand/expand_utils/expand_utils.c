#include "minishell.h"

char	*search_var(char **env, char *name)
{
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(name);
	if (len == 0)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(name, env[i], len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*search_name(char *str, int start)
{
	int		len;
	char	*name;

	len = 0;
	while (ft_isalnum(str[start + len]))
		len++;
	if (len == 0)
		return (NULL);
	name = ft_substr(str, start, len);
	if (!name)
		return (NULL);
	return (name);
}

int	remplace(char **str_new, int j, char *var, int len_var)
{
	char	*pre;
	char	*post;
	char	*new;
	int		len_post;

	if (!var)
		var = "";
	len_post = len_var + 1 + j;
	pre = ft_substr(*str_new, 0, j);
	if (!pre)
		return (1);
	post = ft_substr(*str_new, len_post, ft_strlen(*str_new) - len_post);
	if (!post)
		return (free_3var(&pre, NULL, NULL, 1));
	new = ft_strjoin_var(3, pre, var, post);
	if (!new)
		return (free_3var(&pre, &post, NULL, 1));
	free_3var(&pre, &post, str_new, 0);
	*str_new = new;
	return (0);
}

int	expand_exit_code(t_shell *shell, int j)
{
	char	*ex_val;

	ex_val = ft_itoa(shell->data->exit_code);
	if (!ex_val)
		return (1);
	if (remplace(&shell->expand->current_str, j, ex_val, ft_strlen(ex_val)))
	{
		free(ex_val);
		return (1);
	}
	free(ex_val);
	return (0);
}
