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

char	**join_av_exp(char **ex, char **av, int i)
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

char	**add_av_exp(char **env, char **av)
{
	int		i;
	int		len;
	int		nbr_av;
	char	**ex;

	i = 0;
	len = ft_len_array(env);
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
	ex = join_av_exp(ex, av, i);
	return (ex);
}

int inv_av(char **av)
{
	int	i;
	int j;
	int av_val;

	i = 0;
	av_val = 0;
	while(av[i])
	{
		j = 0;
		while(av[i][j])
		{
			if (av[i][j] == '=')
				av_val++;
			j++;
		}
		i++;
	}
	if (av_val > 0)
		return (av_val);
	return (0);
}
char	**join_av_env(char **ex, char **av, int i)
{
	int	j;

	j = 1;
	while (av[j])
	{
		if(check_sign(av[j]) == 1)
		{ 
			ex[i] = ft_strdup(av[j]);
			if (!ex[i])
			{
				ft_free_split(ex);
				return (NULL);
			}
		}
		j++;
		i++;
	}
	ex[i] = NULL;
	return (ex);
}

char	**add_av_env(char **env, char **av)
{
	int		i;
	int		len;
	int		nbr_av;
	char	**ex;

	i = 0;
	len = ft_len_array(env);
	nbr_av = inv_av(av);
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
	ex = join_av_env(ex, av, i);
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

void	export(t_shell *shell)
{
	if (strlen_av(shell->cmd->arg) == 1)
	{
		shell->data->exp = cp_ex(shell->data->exp);
		tri_bubule(shell->data->exp);
		show_ex(shell->data->exp);
	}
	if (strlen_av(shell->cmd->arg) > 1)
	{
		if (error_export(shell->cmd->arg) == 1)
			return ;
		shell->data->exp = add_av_exp(shell->data->exp, shell->cmd->arg);
		shell->data->env = add_av_env(shell->data->env, shell->cmd->arg);
	}
	return ;
}
