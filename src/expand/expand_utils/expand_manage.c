#include "minishell.h"

int	expand_without_quote(t_shell *shell, char ***arg, int *i, int *j)
{
	int		result;

	if ((*arg)[*i][*j] == '$')
	{
		result = exit_code_expand(shell, *arg, i, j);
		if (result)
			return (result);
		if ((*arg)[*i][*j + 1] && ft_isalnum((*arg)[*i][*j + 1]))
		{
			if (search_expand(shell, arg, i, j))
				return (1);
			return (2);
		}
	}
	return (0);
}

static int	double_quote(t_shell *shell, char **arg, int *i, int *j)
{
	int		end;
	int		result;

	end = *j + 1;
	while (arg[*i][end] && arg[*i][end] != '\"')
	{
		if (arg[*i][end] == '$')
		{
			result = exit_code_expand(shell, arg, i, &end);
			if (result == 1)
				return (1);
			if (result == 2)
				continue ;
			if (arg[*i][end + 1] && ft_isalnum(arg[*i][end + 1]))
			{
				if (search_expand(shell, &arg, i, &end) == 1)
					return (1);
				continue ;
			}
		}
		end++;
	}
	*j = end + 1;
	return (0);
}

int	quote_process(t_shell *shell, char ***arg, int *i, int *j)
{
	if ((*arg)[*i][*j] == '\'')
	{
		(*j)++;
		while ((*arg)[*i][*j] != '\'')
			(*j)++;
		(*j)++;
		return (2);
	}
	else if ((*arg)[*i][*j] == '\"')
	{
		if (double_quote(shell, *arg, i, j) == 1)
			return (1);
		return (2);
	}
	return (0);
}
