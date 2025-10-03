#include "minishell.h"

static void	append_here_doc(char *line, int index, int *len, int *i)
{
	if (line[index + *i - 1] == '<')
	{
		if (line[index + *i] == '<')
		{
			(*i)++;
			(*len)++;
		}
	}
	if (line[index + *i - 1] == '>')
	{
		if (line[index + *i] == '>')
		{
			(*i)++;
			(*len)++;
		}
	}
}

int	metachar(char *line, int index, int *len)
{
	int	i;

	i = 0;
	if (line[index + i] == '<' || line[index + i] == '>'
		|| line[index + i] == '|')
	{
		i++;
		(*len)++;
		append_here_doc(line, index, len, &i);
	}
	return (i);
}
