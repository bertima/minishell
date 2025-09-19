#include "minishell.h"

static void	programme(char *line, t_shell *shell)
{
	if (put_prompt(line, shell))
		return ;
	if (parsing(shell))
		return ;
	if (exec(shell))
		return ;
	free_command_redir_token(shell);
}

int	main(int ac, char **av, char **environ)
{
	char			*line;
	t_shell			shell;

	if (ac != 1 || !av[0])
		return (return_err_int(NULL, "No argument for shell !\n"));
	line = NULL;
	if (init_struct(&shell, environ))
		return (return_err_int(&shell, NULL));
	while (1)
		programme(line, &shell);
	all_free(&shell);
	rl_clear_history();
	return (0);
}
