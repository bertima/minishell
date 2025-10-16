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
		free(*w_dir); 
		*w_dir = ft_strdup("/$");
		if (!*w_dir)
			return (1);
		return (0);
	}
	split_path = ft_split(*w_dir, "/");
	if (!split_path)
		return (1);
	free(*w_dir);
	len = ft_len_array(split_path);
	if (join_dir(w_dir, split_path, len))
		return ((ft_free_split(split_path), 1));
	ft_free_split(split_path);
	return (0);
}

/*static char	*recup_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			return (env[i] + 4);
		i++;
	}
	return (NULL);
}*/

char *recup_wd(t_shell *shell)
{
	char *w_dir;

	w_dir = getcwd(NULL, 0);
	if (!w_dir)
	{
		perror("minishell: répertoire courant inaccessible ou supprimé");

		// On change vers la racine "/" au lieu de $HOME
		if (chdir("/") == -1)
		{
			perror("minishell: impossible de changer vers la racine /");
			return error_find_char(shell, -1, 1, NULL);
		}

		// Nouvelle tentative pour récupérer le chemin après chdir("/")
		w_dir = getcwd(NULL, 0);
		if (!w_dir)
		{
			perror("minishell: getcwd après chdir / a échoué");
			return error_find_char(shell, -1, 1, NULL);
		}
	}
	if (path(&w_dir))
	{
		free(w_dir);  // Pense à libérer si path échoue
		return error_find_char(shell, -1, 1, NULL);
	}
	return w_dir;
}

int	put_prompt(char *line, t_shell *shell)
{
	shell->data->w_dir_prompt = recup_wd(shell);
	if (!shell->data->w_dir_prompt)
		return (1);
	line = readline(shell->data->w_dir_prompt);
	if (!line)
	{
		all_free(shell);
		free(shell->data->w_dir_prompt);
		printf("exit\n");
		exit(127);
		//perror(NULL);
		//return (error_find_int(shell, -1, 1, NULL));
	}
	if (*line)
		add_history(line);
	shell->data->line = ft_strdup(line);
	if (!shell->data->line)
		return (free(line), free(shell->data->w_dir_prompt), 1);
	free(line);
	free(shell->data->w_dir_prompt);
	line = NULL;
	shell->data->w_dir_prompt = NULL;
	return (0);
}
