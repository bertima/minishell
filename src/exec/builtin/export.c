#include "minishell.h"

void	show_ex(char **av)
{
	int	i;
	int	len;

	i = 0;
	len = ft_len_array(av);
	while (i < len)
	{
		printf("declare -x %s\n", av[i]);
		i++;
	}
}

void	tri_bubule(char **ex)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	len = ft_len_array(ex);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			if (ft_strcmp(ex[j], ex[j + 1]) > 0)
			{
				tmp = ex[j];
				ex[j] = ex[j + 1];
				ex[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**cp_ex(char **env)
{
	int		i;
	int		len;
	char	**ex;

	i = 0;
	len = ft_len_array(env);
	ex = calloc(len + 1, sizeof(char *));
	if (!ex)
		return (NULL);
	while (i < len)
	{
		ex[i] = ft_strdup(env[i]);
		if (!ex[i])
		{
			ft_free_split(ex);
			return (NULL);
		}
		i++;
	}
	ex[i] = NULL;
	return (ex);
}

void	export(char **env, char **av)
{
	char	**tmp;

	if (strlen_av(av) != 1)
		return ;
	if (strlen_av(av) == 1)
	{
		tmp = cp_ex(env);
		tri_bubule(tmp);
		show_ex(tmp);
	}
}
