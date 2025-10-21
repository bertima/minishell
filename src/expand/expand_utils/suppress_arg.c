#include "minishell.h"

int	suppress_arg(char ***arg, int *i)
{
	char	**temp;
	int		j;
	int		k;

	j = 0;
	k = 0;
	temp = calloc(ft_len_array(*arg), sizeof(char *));
	if (!temp)
		return (1);
	while ((*arg)[j])
	{
		if (j == *i)
			ft_free(&(*arg)[j]);
		else
			temp[k++] = (*arg)[j];
		j++;
	}
	temp[k] = NULL;
	(*i)--;
	free(*arg);
	*arg = temp;
	return (0);
}
