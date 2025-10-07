#include "minishell.h"

static void	programme(char *line, t_shell *shell)
{
	if (put_prompt(line, shell))
		return ;
	if (parsing(shell))
		return ;
	if (expand(shell, shell->cmd, 0, 0))
		return ;
	if (redirection_verif(shell, NULL))
		return ;
	exec(shell);
}

int	main(int ac, char **av, char **environ)
{
	char			*line;
	t_shell			shell;

	if (ac != 1 || !av[0])
		return (return_err_int(NULL, "No argument for shell !\n"));
	signal_break(SIGINT, gst_handler);
	ignore_signal(SIGQUIT);
	line = NULL;
	if (init_struct(&shell, environ))
		return (return_err_int(&shell, NULL));
	while (1)
	{
		programme(line, &shell);
		free_command_redir_token_children(&shell);
	}
	all_free(&shell);
	return (0);
}
