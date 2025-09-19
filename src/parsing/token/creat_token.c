#include "minishell.h"

static int	add_back_token(t_shell *shell, int i, int j)
{
	t_token	*temp;

	temp = shell->token;
	while (temp->next)
		temp = temp->next;
	temp->next = ft_calloc(1, sizeof(t_token));
	if (!temp->next)
		return (1);
	temp->next->sentence = ft_substr(shell->data->line, i, j);
	if (!temp->next->sentence)
		return (1);
	return (0);
}

static int	add_token(t_shell *shell, int i, int j)
{
	if (!shell->token)
	{
		shell->token = ft_calloc(1, sizeof(t_token));
		if (!shell->token)
			return (1);
		shell->token->sentence = ft_substr(shell->data->line, i, j);
		if (!shell->token->sentence)
			return (1);
	}
	else
	{
		if (add_back_token(shell, i, j))
			return (1);
	}
	return (0);
}

static int	find_quote(t_shell *shell, char *line, int *len, char c)
{
	int	j;	

	j = 1;
	while (line[j] && line[j] != c)
		j++;
	if (!line[j])
		return (return_err_int(shell, "Quote no close !\n"));
	*len += j + 1;
	return (0);
}

static int	loop(t_shell *shell, char *line, int start, int *len)
{
	int	index;
	int	meta;

	*len = 0;
	index = start;
	while (line[index] && !ft_isspace(line[index]))
	{
		meta = metachar(line, index);
		if (meta > 0)
		{
			if (*len == 0)
				*len = meta;
			break ;
		}
		if ((line[index] == '\'' || line[index] == '\"'))
		{
			if (find_quote(shell, &line[index], len, line[index]))
				return (1);
		}
		else
			(*len)++;
		index = start + *len;
	}
	return (0);
}

int	tokening(t_shell *shell)
{
	char	*line;
	int		start;
	int		len;

	start = 0;
	len = 0;
	line = shell->data->line;
	while (line[start])
	{
		while (line[start] && ft_isspace(line[start]))
			start++;
		if (!line[start])
			break ;
		if (loop(shell, line, start, &len))
			return (1);
		if (add_token(shell, start, len))
			return (1);
		start += len;
		len = 0;
	}
	return (0);
}
