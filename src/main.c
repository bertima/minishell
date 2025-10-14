#include "minishell.h"

static void	programme(char *line, t_shell *shell)
{
	if (put_prompt(line, shell))
		return ;
	if (parsing(shell))
		return ;
	if (expand(shell, shell->cmd, 0, 0))
		return ;
	if (here_doc(shell, NULL))
		return ;
	exec(shell);
}

int	main(int ac, char **av, char **environ)
{
	char			*line;
	t_shell			shell;

	if (ac != 1 || !av[0])
		return (error_find_int(NULL, ARG_MINISHELL, 1, NULL));
	line = NULL;
	if (init_struct(&shell, environ))
		return (1);
	shell.data->exit_code = signal_break(SIGINT, gst_handler);
	ignore_signal(SIGQUIT);
	while (1)
	{
		programme(line, &shell);
		free_command_redir_token_children(&shell);
	}
	all_free(&shell);
	return (0);
}
