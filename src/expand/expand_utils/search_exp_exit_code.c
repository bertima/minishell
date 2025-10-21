#include "minishell.h"

static int	remplace(char **str_new, int j, char *var, int len_var)
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
		return (free(pre), 1);
	new = ft_strjoin_var(3, pre, var, post);
	if (!new)
		return (free(pre), free(post), 1);
	free(*str_new);
	*str_new = new;
	return (free(pre), free(post), 0);
}

int	exit_code_expand(t_shell *shell, char **arg, int *i, int *end)
{
	char	*nbr;

	if (arg[*i][*end + 1] == '?')
	{
		nbr = ft_itoa(shell->data->exit_code);
		if (remplace(&arg[*i], *end, nbr, ft_strlen(nbr)))
		{
			free(nbr);
			return (1);
		}
		*end += ft_strlen(nbr);
		free(nbr);
		return (2);
	}
	return (0);
}

static char	*search_var(char **env, char *name)
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

int	search_expand(t_shell *shell, char ***arg, int *i, int *j)
{
	char	c;
	char	*var;
	char	*name;

	name = NULL;
	c = (*arg)[*i][*j + 1];
	if ((*arg)[*i][*j] == '$' && c && ft_valid_expand(c))
	{
		name = search_name((*arg)[*i], *j + 1);
		if (name)
		{
			var = search_var(shell->data->env, name);
			if (var)
			{
				if (remplace(&(*arg)[*i], *j, var, ft_strlen(name)))
					return (ft_free(&name), 1);
				*j += ft_strlen(var);
				return (ft_free(&name), 0);
			}
		}
		if (remplace(&(*arg)[*i], *j, NULL, ft_strlen(name)))
			return (ft_free(&name), 1);
	}
	ft_free(&name);
	return (0);
}
