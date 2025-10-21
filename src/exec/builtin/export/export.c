#include "minishell.h"

char	**add_var_to_env(char **env, char *var, int i, int len)
{
	char	**new_env;

	len = ft_len_array(env);
	new_env = ft_calloc(len + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			ft_free_split(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
	{
		ft_free_split(new_env);
		return (NULL);
	}
	return (new_env);
}

char	**update_or_add_env(char **env, char *var)
{
	int		index;
	char	*new_var;
	char	**new_env;

	if (!var)
		return (env);
	new_var = remove_quotes_value(var);
	if (!new_var)
		return (NULL);
	index = var_exists(env, var);
	if (index != -1)
	{
		ft_free(&env[index]);
		env[index] = new_var;
		return (env);
	}
	new_env = add_var_to_env(env, new_var, 0, 0);
	ft_free(&new_var);
	if (!new_env)
		return (NULL);
	ft_free_split(env);
	return (new_env);
}

char	**update_exp(char **exp, char *var, char *new_var, int i)
{
	char	**new_exp;

	i = var_exists(exp, var);
	if (i != -1)
	{
		if (ft_strchr(var, '='))
		{
			new_var = quote_value(var);
			if (!new_var)
				return (NULL);
			ft_free(&exp[i]);
			exp[i] = new_var;
		}
		return (exp);
	}
	new_var = quote_value(var);
	if (!new_var)
		return (NULL);
	new_exp = add_var_to_env(exp, new_var, 0, 0);
	ft_free(&new_var);
	if (!new_exp)
		return (NULL);
	ft_free_split(exp);
	return (new_exp);
}

void	update_all(t_shell *shell, char **av)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if ((av[i][0] == '_') || (av[i][0] >= 'a' && av[i][0] <= 'z')
		|| (av[i][0] >= 'A' && av[i][0] <= 'Z'))
		{
			update(shell, av, i);
		}
		else
		{
			ft_putstr_fd("bash: export: '", 2);
			ft_putstr_fd(av[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			shell->data->exit_code = 1;
		}
		i++;
	}
}

void	export(t_shell *shell, char **args, char **tmp)
{
	args = shell->cmd->arg;
	if (ft_len_array(args) == 1)
	{
		tmp = cp_ex(shell->data->exp);
		if (!tmp)
			return ;
		tmp = normalize_export(tmp);
		if (!tmp)
			return ;
		tri_bubule(tmp);
		show_ex(tmp);
		shell->data->exit_code = 0;
		ft_free_split(tmp);
	}
	else
	{
		shell->data->exit_code = 0;
		if (error_export(args))
		{
			shell->data->exit_code = 1;
			return ;
		}
		update_all(shell, args);
	}
}
