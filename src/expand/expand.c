#include "minishell.h"

static int	loop_remove_quote(t_cmd *cmd, int stock, int i)
{
	int	j;

	j = 0;
	while (cmd->arg && cmd->arg[stock] && stock <= i)
	{
		j = 0;
		while (cmd->arg[stock] && cmd->arg[stock][j])
		{
			if (cmd->arg[stock][j] == '\"' || cmd->arg[stock][j] == '\'')
			{
				if (remove_quote(&cmd->arg[stock], &j))
					return (1);
			}
			else
				j++;
		}
		stock++;
	}
	return (0);
}

static int	verfi_new_arg(t_cmd *cmd, int *i, int *start_end, int *j)
{
	start_end[1] = *j;
	if (start_end[1] > start_end[0])
	{
		start_end[1] = *j;
		if (insert_arg_expand(cmd, start_end, i, j))
			return (1);
	}
	return (0);
}

static int	loop_word_split(t_cmd *cmd, int *i, int j, int block)
{
	int	start_end[2];

	if (!cmd->arg[*i][0])
		return (suppress_arg(cmd, i));
	start_end[0] = 0;
	while (cmd->arg[*i] && cmd->arg[*i][j])
	{
		if ((cmd->arg[*i][j] == '\'' || cmd->arg[*i][j] == '\"'))
		{
			if (block == 0)
			{
				if (verfi_new_arg(cmd, i, start_end, &j))
					return (1);
				block = 1;
			}
			else
			{
				block = 0;
				start_end[0] = j + 1;
			}
		}
		j++;
	}
	return (verfi_new_arg(cmd, i, start_end, &j));
}

static int	loop_expand(t_shell *shell, t_cmd *cmd, int *i, int *j)
{
	int			result;
	int			stock;

	stock = *i;
	while (cmd->arg && cmd->arg[*i] && cmd->arg[*i][*j])
	{
		result = quote_process(shell, cmd, i, j);
		if (result == 1)
			return (1);
		if (result == 2)
			continue ;
		result = expand_without_quote(shell, cmd, i, j);
		if (result == 1)
			return (1);
		if (result == 2)
			continue ;
		(*j)++;
	}
	if (loop_word_split(cmd, i, 0, 0))
		return (1);
	if (loop_remove_quote(cmd, stock, *i))
		return (1);
	return (0);
}

int	expand(t_shell *shell, t_cmd *cmd, int i, int j)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		i = 0;
		shell->expand->cmd = temp;
		while (temp->arg && temp->arg[i])
		{
			j = 0;
			shell->expand->current_str = temp->arg[i];
			if (loop_expand(shell, temp, &i, &j))
				return (1);
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
