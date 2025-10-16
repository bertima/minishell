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

	c = (*arg)[*i][*j + 1];
	if ((*arg)[*i][*j] == '$' && c && ft_isalnum(c))
	{
		name = search_name((*arg)[*i], *j + 1);
		if (name)
		{
			var = search_var(shell->data->env, name);
			if (var)
			{
				if (remplace(&(*arg)[*i], *j, var, ft_strlen(name)))
					return (free(name), 1);
				*j += ft_strlen(var);
				return (free (name), 0);
			}
		}
		if (remplace(&(*arg)[*i], *j, NULL, ft_strlen(name)))
			return (free(name), 1);
	}
	return (0);
}

int	suppress_arg(char ***arg, int *i)
{
	char	**temp;
	int		j;
	int		k;

	j = 0;
	k = 0;
	temp = calloc(ft_len_array(*arg), sizeof(char *));
	if (!temp)
		return (1);
	while ((*arg)[j])
	{
		if (j == *i)
		{
			free((*arg)[j]);
			(*arg)[j] = NULL;
		}
		else
			temp[k++] = (*arg)[j];
		j++;
	}
	temp[k] = NULL;
	(*i)--;
	free(*arg);
	*arg = temp;
	return (0);
}
