#include "minishell.h"

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
	len = ft_len_double_char(split_path);
	*w_dir = ft_strjoin_var(3, "~/", split_path[len - 1], "$ ");
	if (!*w_dir)
		return (1);
	return (0);
}

static char	*recup_wd(t_shell *shell)
{
	char	*w_dir;

	w_dir = getcwd(NULL, 0);
	if (!w_dir)
		return (return_null(shell));
	if (path(&w_dir))
		return (return_null(shell));
	return (w_dir);
}

int	put_prompt(char *line, t_shell *shell)
{
	char	*w_dir;

	w_dir = recup_wd(shell);
	if (!w_dir)
		return (return_err_int(shell, "Error getcwd !\n"));
	line = readline(w_dir);
	if (!line)
	{
		all_free(shell);
		rl_clear_history();
		printf("exit\n");
		exit(127);
		//perror(NULL);
		//return (return_err_int(shell, "Error readline !\n"));
	}
	if (*line)
		add_history(line);
	shell->data->line = ft_strdup(line);
	if (!shell->data->line)
	{
		free(line);
		free(w_dir);
		return (return_err_int(shell, "Error malloc !\n"));
	}
	free(line);
	free(w_dir);
	line = NULL;
	w_dir = NULL;
	return (0);
}
