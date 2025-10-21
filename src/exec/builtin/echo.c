#include "minishell.h"

static void	flag_exist(char **str, int *i, int *flag, int j)
{
	int	len;

	while (str[*i])
	{
		len = ft_strlen(str[*i]);
		j = 0;
		while (str[*i] && str[*i][j])
		{
			if (str[*i][j] && str[*i][j] != '-')
				return ;
			j++;
			while (str[*i][j] && str[*i][j] == 'n')
				j++;
			if (j < len)
				return ;
			(*flag)++;
		}
		(*i)++;
	}
}

void	echo(t_shell *shell, char **str)
{
	int	i;
	int	j;
	int	flag;

	j = 0;
	i = 1;
	flag = 0;
	flag_exist(str, &i, &flag, 0);
	while (str && str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 0)
		printf("\n");
	shell->data->exit_code = 0;
}
