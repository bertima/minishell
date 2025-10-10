#include "minishell.h"

static int	join_dir(char **w_dir, char **split_path, int len)
{
	char	*first;
	char	*last;

	first = ft_strdup("~/");
	if (!first)
		return (free(*w_dir), 1);
	last = ft_strdup("$ ");
	if (!last)
		return (free(w_dir), free(first), 1);
	*w_dir = ft_strjoin_var(3, first, split_path[len - 1], last);
	if (!*w_dir)
		return (1);
	free(first);
	free(last);
	first = NULL;
	last = NULL;
	return (0);
}

static int	path(char **w_dir)
{
	char	**split_path;
	int		len;

	if (ft_strcmp(*w_dir, "/") == 0)
	{
		*w_dir = ft_strdup("/$");
		if (!*w_dir)
			return (1);
		return (0);
	}
	split_path = ft_split(*w_dir, "/");
	if (!split_path)
		return (1);
	len = ft_len_array(split_path);
	if (join_dir(w_dir, split_path, len))
		return ((ft_free_split(split_path), 1));
	ft_free_split(split_path);
	return (0);
}

char	*recup_wd(t_shell *shell, char *w_dir, char *fallback)
{
	w_dir = getcwd(NULL, 0);
	if (!w_dir)
	{
		perror("minishell: getcwd");
		fallback = getenv("PWD");
		if (!fallback)
		{
			fprintf(stderr, "minishell: cd : fallback to /\n");
			fallback = "/";
		}
		if (chdir(fallback) != 0)
		{
			perror("minishell: chdir fallback failed");
			return (return_null(shell));
		}
		w_dir = getcwd(NULL, 0);
		if (!w_dir)
		{
			perror("minishell: getcwd after chdir");
			return (return_null(shell));
		}
	}
	if (path(&w_dir))
		return (return_null(shell));
	return (w_dir);
}

int	put_prompt(char *line, t_shell *shell)
{
	char	*w_dir;

	w_dir = recup_wd(shell, NULL, NULL);
	if (!w_dir)
		return (return_err_int(shell, "Error getcwd !\n"));
	line = readline(w_dir);
	if (!line)
	{
		all_free(shell);
		printf("exit\n");
		exit(127);
		perror(NULL);
		return (return_err_int(shell, "Error readline !\n"));
	}
	if (*line)
		add_history(line);
	shell->data->line = ft_strdup(line);
	if (!shell->data->line)
		return (free(line), free(w_dir), 1);
	free(line);
	free(w_dir);
	line = NULL;
	w_dir = NULL;
	return (0);
}
