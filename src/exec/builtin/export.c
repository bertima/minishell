#include "minishell.h"

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
		i++;
		j++;
	}
	ex[i] = NULL;
	return (ex);
}

char	**add_av_exp(char **env, char **av)
{
	char	**ex;
	int		i;
	int		len;
	int		nbr_av;

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
	return (join_av_exp(ex, av, i));
}

char	**join_av_env(char **ex, char **av, int i)
{
	int	j;

	j = 1;
	while (av[j])
	{
		if (check_sign(av[j]) == 1)
		{
			ex[i] = ft_strdup(av[j]);
			if (!ex[i])
			{
				ft_free_split(ex);
				return (NULL);
			}
			i++;
		}
		j++;
	}
	ex[i] = NULL;
	return (ex);
}

char	**add_av_env(char **env, char **av)
{
	char	**ex;
	int		i;
	int		len;
	int		nbr_av;

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
	return (join_av_env(ex, av, i));
}

void	export(t_shell *shell)
{
	char	**tmp;

	if (strlen_av(shell->cmd->arg) == 1)
	{
		tmp = cp_ex(shell->data->exp);
		if (!tmp)
			return ;
		tri_bubule(tmp);
		show_ex(tmp);
		ft_free_split(tmp);
	}
	else if (strlen_av(shell->cmd->arg) > 1)
	{
		if (error_export(shell->cmd->arg))
			return ;
		tmp = add_av_exp(shell->data->exp, shell->cmd->arg);
		if (!tmp)
			return ;
		ft_free_split(shell->data->exp);
		shell->data->exp = tmp;
		tmp = add_av_env(shell->data->env, shell->cmd->arg);
		if (!tmp)
			return ;
		ft_free_split(shell->data->env);
		shell->data->env = tmp;
	}
}