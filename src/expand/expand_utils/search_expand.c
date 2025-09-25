#include "minishell.h"

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

int	search_expand(t_shell *shell, t_cmd *cmd, int *i, int *j)
{
	char	c;
	char	*var;
	char	*name;

	c = cmd->arg[*i][*j + 1];
	if (cmd->arg[*i][*j] == '$' && c && ft_isalnum(c))
	{
		name = search_name(cmd->arg[*i], *j + 1);
		if (name)
		{
			var = search_var(shell->data->env, name);
			if (var)
			{
				if (remplace(&cmd->arg[*i], *j, var, ft_strlen(name)))
					return (1);
				*j = ft_strlen(var);
				return (0);
			}
		}
		if (remplace(&cmd->arg[*i], *j, NULL, ft_strlen(name)))
			return (1);
	}
	return (0);
}

int	suppress_arg(t_cmd *cmd, int *i)
{
	char	**temp;
	int		j;
	int		k;

	j = 0;
	k = 0;
	temp = calloc(ft_len_array(cmd->arg), sizeof(char *));
	if (!temp)
		return (1);
	while (cmd->arg[j])
	{
		if (j == *i)
			free(cmd->arg[j]);
		else
			temp[k] = cmd->arg[j];
		j++;
	}
	temp[k] = NULL;
	free(cmd->arg);
	cmd->arg = temp;
	return (0);
}
