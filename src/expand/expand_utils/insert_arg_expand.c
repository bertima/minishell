#include "minishell.h"

static int	regroupe(char ***new, char *str, int *start_end, char *temp)
{
	char	*pre;
	char	*post;

	pre = ft_substr(str, 0, start_end[0]);
	if (!pre)
		return (1);
	temp = ft_strjoin(pre, (*new)[0]);
	if (!temp)
		return (free(pre), 1);
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

static int	creat_new(char ***new, char **str_arg, int *start_end, int *j)
{
	*new = ft_split(str_arg[1], " \t\n");
	if (!*new)
		return (1);
	*j = ft_strlen((*new)[ft_len_array(*new) - 1]);
	if (regroupe(new, str_arg[0], start_end, NULL))
		return (ft_free_split(*new), 1);
	return (0);
}

static void	copie_continue(t_cmd *cmd, int *i, char ***temp, int j)
{
	while (cmd->arg[*i] && cmd->arg[*i + 1])
	{
		(*temp)[j] = cmd->arg[1 + *i];
		(*i)++;
		j++;
	}
	(*temp)[j] = NULL;
}

static int	copie_cmd(t_cmd *cmd, char **new, int *i, int stock)
{
	int		j;
	int		k;
	int		len;
	char	**temp;

	j = -1;
	k = 0;
	len = ft_len_array(cmd->arg) + ft_len_array(new);
	temp = calloc(len + 1, sizeof(char *));
	if (!temp)
		return (1);
	while (++j < *i)
		temp[j] = cmd->arg[j];
	while (new[k])
		temp[j++] = new[k++];
	stock = j - 1;
	copie_continue(cmd, i, &temp, j);
	free(cmd->arg);
	cmd->arg = temp;
	*i = stock;
	return (0);
}

int	insert_arg_expand(t_cmd *cmd, int *start_end, int *i, int *j)
{
	char	*str_arg[2];
	char	**new;

	str_arg[1] = ft_substr(cmd->arg[*i], start_end[0], start_end[1]);
	if (!str_arg[1])
		return (1);
	str_arg[0] = cmd->arg[*i];
	if (creat_new(&new, str_arg, start_end, j))
		return (free(str_arg[1]), 1);
	if (copie_cmd(cmd, new, i, 0))
		return (1);
	return (0);
}
