#include "minishell.h"

static void	programme(char *line, t_shell *shell)
{
	put_prompt(line, shell);
	parsing(shell);
	exec(shell);
	free_command_redir_token(shell);
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
		programme(line, &shell);
	all_free(&shell);
	rl_clear_history();
	return (0);
}
