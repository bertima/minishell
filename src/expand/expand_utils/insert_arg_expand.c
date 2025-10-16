#include "minishell.h"

static int	regroupe(char ***new, char *str, int *start_end, int *j)
{
	char	*temp;
	char	*pre;
	char	*post;

	pre = ft_substr(str, 0, start_end[0]);
	if (!pre)
		return (1);
	temp = ft_strjoin(pre, (*new)[0]);
	if (!temp)
		return (free(pre), 1);
	*j = ft_strlen(temp);
	free((*new)[0]);
	free(pre);
	(*new)[0] = temp;
	post = ft_substr(str, start_end[1], ft_strlen(str));
	if (!post)
		return (1);
	temp = ft_strjoin((*new)[ft_len_array(*new) - 1], post);
	if (!temp)
		return (free(post), 1);
	free((*new)[ft_len_array(*new) - 1]);
	free(post);
	(*new)[ft_len_array(*new) - 1] = temp;
	return (0);
}

static void	copie_post_new(char ***arg, int *i, char ***temp, int j)
{
	while ((*arg)[*i] && (*arg)[*i + 1])
	{
		(*temp)[j] = (*arg)[1 + *i];
		(*i)++;
		j++;
	}
	(*temp)[j] = NULL;
}

static int	copie_new(char **new, int *j, char ***temp)
{
	int	k;

	k = 0;
	while (new[k])
	{
		(*temp)[*j] = ft_strdup(new[k]);
		if (!(*temp)[*j])
			return (ft_free_split(new), 1);
		free(new[k]);
		new[k] = NULL;
		(*j)++;
		k++;
	}
	free(new);
	new = NULL;
	return (0);
}

static int	copie_cmd(char ***arg, char **new, int *i, int stock)
{
	int		j;
	int		k;
	int		len;
	char	**temp;

	j = -1;
	k = 0;
	len = ft_len_array(*arg) + ft_len_array(new);
	temp = calloc(len + 1, sizeof(char *));
	if (!temp)
		return (1);
	while (++j < *i)
		temp[j] = (*arg)[j];
	if (copie_new(new, &j, &temp))
		return (1);
	stock = j - 1;
	copie_post_new(arg, i, &temp, j);
	free(*arg);
	(*arg) = temp;
	*i = stock;
	return (0);
}

int	insert_arg_expand(char ***arg, int *start_end, int *i, int *j)
{
	int		len;
	char	*str_arg[2];
	char	**new;

	len = start_end[1] - start_end[0];
	if (start_end[0] >= start_end[1])
		return (0);
	str_arg[0] = ft_substr((*arg)[*i], start_end[0], len);
	if (!str_arg[0])
		return (1);
	str_arg[1] = (*arg)[*i];
	new = ft_split(str_arg[0], " \t\n\v\f\r");
	if (!new)
		return (1);
	if (regroupe(&new, str_arg[1], start_end, j))
		return (ft_free_split(new), free(str_arg[0]), 1);
	if (copie_cmd(arg, new, i, 0))
		return (1);
	free(str_arg[0]);
	return (0);
}
