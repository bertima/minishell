#include "minishell.h"

/*echo print ce qu'il y a derriere
-n evite le retour a la ligne*/

static void	flag_exist(char **str, int i)
{
	i += 1;
	if (!str[i])
		return ;
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
}

void	echo(char **str)
{
	int	i;

	i = 1;
	while (str && str[0] && str[i])
	{
		if (ft_strcmp(str[1], "-n") == 0)
		{
			flag_exist(str, i);
			return ;
		}
		else
		{
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
		}
		i++;
	}
	printf("\n");
}
