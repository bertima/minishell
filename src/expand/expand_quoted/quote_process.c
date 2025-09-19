#include "minishell.h"

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
				if (search_expand(shell, shell->expand->cmd, i, &end))
					return (1);
				continue ;
			}
		}
		end++;
	}
	return (0);
}

int	quote_process(t_shell *shell, t_cmd *cmd, int *i, int *j)
{
	if (cmd->arg[*i][*j] == '\'')
	{
		if (remove_quote(&cmd->arg[*i], j))
			return (1);
		return (2);
	}
	else if (cmd->arg[*i][*j] == '\"')
	{
		shell->expand->name_var = search_name(cmd->arg[*i], *j);
		if (double_quote(shell, cmd->arg, i, j) == 1)
			return (1);
		if (remove_quote(&cmd->arg[*i], j))
			return (1);
		return (2);
	}
	return (0);
}
