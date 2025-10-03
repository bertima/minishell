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
char	**add_av(char **env,char **av, int j)
{
	int		i;
	int		len;
	int 	nbr_av;
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
	while(av[j])
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
		if (av[1][0] == '-')
		{
			printf("les consigne ne demande pas de gere les option!\n");
			return(env);
		}
		if (av[1][0] == '*' && av[1][1] == '\0')
		{
			printf("la gestion de * faite partie des bonus\n");
			return(env);
		}
		if ((av[1][0] != '_') && (av[1][0] < 'a' || av[1][0] > 'z') && (av[1][0] < 'A' || av[1][0] > 'Z'))
		{
			printf("bash: export: %s : not a valid identifier\n", av[1]);
			return (env);
		}
		env = add_av(env, av, 1);
		return (env);
	}
	return (env);
}
