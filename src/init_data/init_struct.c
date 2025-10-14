#include "minishell.h"

static int	creat_env(char ***env)
{
	char	*temp;

	*env = calloc(4, sizeof(char *));
	if (!*env)
		return (1);
	temp = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:");
	if (!temp)
	{
		free(*env);
		return (1);
	}
	(*env)[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	(*env)[1] = ft_strdup("SHLVL=1");
	(*env)[2] = ft_strjoin(temp, "/usr/sbin:/usr/bin:/sbin:/bin");
	(*env)[3] = NULL;
	if (!(*env)[0] || !(*env)[1] || !(*env)[2])
	{
		ft_free_split(*env);
		return (1);
	}
	return (0);
}

static int	cp_env(char ***env, char **environ)
{
	int	i;
	int	len;

	i = 0;
	if (!environ || !environ[0])
		return (creat_env(env));
	len = ft_len_array(environ);
	(*env) = calloc(len + 1, sizeof(char *));
	if (!(*env))
		return (1);
	while (i < len)
	{
		(*env)[i] = ft_strdup(environ[i]);
		if (!(*env)[i])
		{
			ft_free_split((*env));
			return (1);
		}
		i++;
	}
	(*env)[i] = NULL;
	return (0);
}

int	init_struct(t_shell *shell, char **environ)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->data = ft_calloc(1, sizeof(t_data));
	if (!shell->data)
		return (1);
	if (cp_env(&shell->data->env, environ))
		return (1);
	if (cp_env(&shell->data->exp, environ))
		return (1);
	shell->data->fd_stock_in = -1;
	shell->data->fd_stock_out = -1;
	return (0);
}
