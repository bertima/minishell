#include "minishell.h"

int	metachar(char *line, int index, int *len)
{
	int	i;

	i = 0;
	if (line[index + i] == '<' || line[index + i] == '>'
		|| line[index + i] == '|')
	{
		i++;
		(*len)++;
		if (line[index + i] == '<' || line[index + i] == '>')
		{
			i++;
			(*len)++;
		}
	}
	return (i);
}
