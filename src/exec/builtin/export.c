#include "minishell.h"

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

char	**join_av(char **ex, char **av, int i)
{
	int	j;

	j = 1;
	while (av[j])
	{
		ex[i] = ft_strdup(av[j]);
		if (!ex[i])
		{
			ft_free_split(ex);
			return (NULL);
		}
		j++;
		i++;
	}
	ex[i] = NULL;
	return (ex);
}

char	**add_av(char **env, char **av)
{
	int		i;
	int		len;
	int		nbr_av;
	char	**ex;

	i = 0;
	len = ft_len_double_char(env);
	nbr_av = strlen_av(av);
	ex = calloc(len + nbr_av + 1, sizeof(char *));
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
	ex = join_av(ex, av, i);
	return (ex);
}

int	error_export(char **av)
{
	if (av[1][0] == '-')
	{
		printf("les consigne ne demande pas de gere les option!\n");
		return (1);
	}
	if (av[1][0] == '*' && av[1][1] == '\0')
	{
		printf("la gestion de * faite partie des bonus\n");
		return (1);
	}
	if ((av[1][0] != '_') && (av[1][0] < 'a' || av[1][0] > 'z')
		&& (av[1][0] < 'A' || av[1][0] > 'Z'))
	{
		printf("bash: export: %s : not a valid identifier\n", av[1]);
		return (1);
	}
	return (0);
}

char	**export(char **env, char **av)
{
	char	**tmp;

	if (strlen_av(av) == 1)
	{
		tmp = cp_ex(env);
		tri_bubule(tmp);
		show_ex(tmp);
	}
	if (strlen_av(av) > 1)
	{
		if (error_export(av) == 1)
			return (env);
		env = add_av(env, av);
		return (env);
	}
	return (env);
}
