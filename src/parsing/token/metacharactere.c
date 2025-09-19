#include "minishell.h"

int	metachar(char *line, int index)
{
	int	i;

	i = 0;
	while (line[index + i] == '<' || line[index + i] == '>'
		|| line[index + i] == '|')
	{
		if (line[index + i] == '|')
			return (1);
		i++;
	}
	return (i);
}
