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

char	**normalize_export(char **exp)
{
	char	**new_exp;
	char	*quoted_var;
	int		i;
	int		len;

	len = ft_len_array(exp);
	new_exp = ft_calloc(len + 1, sizeof(char *));
	if (!new_exp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		quoted_var = quote_value(exp[i]);
		if (!quoted_var)
		{
			ft_free_split(new_exp);
			return (NULL);
		}
		new_exp[i] = quoted_var;
		i++;
	}
	new_exp[i] = NULL;
	ft_free_split(exp);
	return (new_exp);
}

int	error_export(char **av)
{
	if (av[1][0] == '-')
	{
		ft_putstr_fd("export : No option supported\n", 2);
		return (1);
	}
	if (av[1][0] == '*' && av[1][1] == '\0')
	{
		ft_putstr_fd("export : No supported '*'\n", 2);
		return (1);
	}
	if ((av[1][0] != '_') && (av[1][0] < 'a' || av[1][0] > 'z')
		&& (av[1][0] < 'A' || av[1][0] > 'Z'))
	{
		ft_putstr_fd("bash: export: '%s': not a valid identifier\n", av[1]);
		return (1);
	}
	return (0);
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
	char	**ex;
	int		i;
	int		len;

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
